#include "pch.h"
#include "OptionsState.h"
#include "MainMenuState.h"


void OptionsState::draw(sf::RenderTarget& target, sf::RenderStates) const
{
	target.draw(m_BackgroundSprite);
	target.draw(m_Title);
	target.draw(m_UI);
}

OptionsState::OptionsState(sf::RenderWindow& window, std::stack<State::ptr>& states, sf::Sprite& bgsprite)
	: State(window, states),  m_WinSize{m_Window.getSize()}, m_BackgroundSprite(bgsprite)
{
	initTitle();
	initGUI();
}


/* ==================================      INITIALIZERS      ================================== */


void OptionsState::initTitle()
{
	m_Title.setLetterSpacing(8);
	m_Title.setOutlineThickness(9);
	m_Title.setOutlineColor(sf::Color::Blue);
	sf::Vector2f title_position((m_WinSize.x - m_Title.getSize().x) / 2.f, 150);

	m_Title.setPosition(title_position);

}

void OptionsState::initGUI()
{
	auto vert_layout = std::make_unique<VerticalLayout>(opt_ref(m_UI), 5.f);
		addGUIGraphics(vert_layout);
		initGUIMusic(vert_layout);
	m_UI.addLayout(std::move(vert_layout));

	addGUINavigation();


	m_UI.bind(Configuration::GuiInputs::Escape,
		[this](const sf::Event&) {
			m_ShouldQuit = true;
		});
}

void OptionsState::addGUIGraphics(VerticalLayout::ptr& vert_layout)
{
	addButtonResolutions(vert_layout);
	addButtonFullscreen(vert_layout);
	addButtonVSync(vert_layout);
}

#pragma region GUI

void OptionsState::addButtonResolutions(VerticalLayout::ptr& vert_layout)
{
	std::vector<sf::VideoMode> modes = sf::VideoMode::getFullscreenModes();

	sf::Vector2f size(m_WinSize.x * 0.8f, 75.f);
	std::string	button_text = "Screen   Resolution";
	sf::Font& font = Configuration::fonts.get(Configuration::Fonts::SpaceGui);
	sf::Vector2f area_size(500.f, 75.f);

	auto window_sizes = std::make_unique<ArrowSwitchTextButton>(opt_ref(m_UI), size, button_text, font, 25u, modes.size(), area_size, sf::Vector2f(100, 50));

	for (int i = modes.size() - 1; i >= 0; --i) {
		if (modes[i].width < 1600) 
			continue;

		button_text = std::to_string(modes[i].width) + "   x   " + std::to_string(modes[i].height);
		window_sizes->addOption(button_text, font, 25u);
	}

	vert_layout->add(std::move(window_sizes));

	sf::Vector2f layout_pos;
	layout_pos.x = (static_cast<float>(m_Window.getSize().x) - vert_layout->getSize().x) / 2.f;
	layout_pos.y = m_Title.getPosition().y + m_Title.getSize().y + 50.f;
	vert_layout->setPosition(layout_pos);
}

void OptionsState::addButtonFullscreen(VerticalLayout::ptr& vert_layout)
{
	sf::Vector2f size(m_WinSize.x * 0.8f, 75.f);
	sf::Font& font = Configuration::fonts.get(Configuration::Fonts::SpaceGui);
	sf::Vector2f area_size(500.f, 75.f);

	auto fullscreen = std::make_unique<ArrowSwitchTextButton>(opt_ref(m_UI), size, "Fullscreen", font, 25u, 2, area_size, sf::Vector2f(100, 50));
	fullscreen->addOption("Off", font, 25u);
	fullscreen->addOption("On", font, 25u);

	vert_layout->add(std::move(fullscreen));
}

void OptionsState::addButtonVSync(VerticalLayout::ptr& vert_layout)
{
	sf::Vector2f size(m_WinSize.x * 0.8f, 75.f);
	sf::Font& font = Configuration::fonts.get(Configuration::Fonts::SpaceGui);
	sf::Vector2f area_size(500.f, 75.f);

	auto vsync = std::make_unique<ArrowSwitchTextButton>(opt_ref(m_UI), size, "Vertical   Synchronization", font, 25u, 2, area_size, sf::Vector2f(100, 50));
	vsync->addOption("On", font, 25u);
	vsync->addOption("Off", font, 25u);


	vert_layout->add(std::move(vsync));
}


void OptionsState::initGUIMusic(VerticalLayout::ptr& vert_layout)
{
	sf::Vector2f size(m_WinSize.x * 0.8f, 75.f);
	sf::Font& font = Configuration::fonts.get(Configuration::Fonts::SpaceGui);
	sf::Vector2f area_size(500.f, 75.f);

	auto music = std::make_unique<ArrowSwitchTextButton>(opt_ref(m_UI), size, "Music", font, 25u, 2, area_size, sf::Vector2f(100, 50));
	music->addOption("On", font, 25u);
	music->addOption("Off", font, 25u);
	
	auto volume = std::make_unique<ArrowSwitchTextButton>(opt_ref(m_UI), size, "Volume", font, 25u, 2, area_size, sf::Vector2f(100, 50));
	
	for (int i = 0; i <= 100; i += 25) {
		std::string button_text = std::to_string(i);
		volume->addOption(button_text, font, 25u);
	}

	vert_layout->add(std::move(music));
	vert_layout->add(std::move(volume));






}

void OptionsState::addGUINavigation()
{
	auto unordered_layout = std::make_unique<UnorderedLayout>(opt_ref(m_UI));
	    auto back = std::make_unique<TextButton>(opt_ref(*unordered_layout), std::nullopt, sf::Color::Red, "BACK");
	    back->on_click = [this](const sf::Event&, Button&) {
	    	m_ShouldQuit = true;
	    };
	    back->setPosition(sf::Vector2f(0, 0));
	    
	    unordered_layout->add(std::move(back));
	m_UI.addLayout(std::move(unordered_layout));


	auto horizontal_layout = std::make_unique<HorizontalLayout>(opt_ref(m_UI), 5.f);
	    auto apply = std::make_unique<TextButton>(opt_ref(*horizontal_layout), std::nullopt, sf::Color::Red, "APPLY");
		apply->on_click = [this](const sf::Event&, Button&) {
	    	readAndApplyButtonData();
	    };
	    horizontal_layout->add(std::move(apply));

	    auto save = std::make_unique<TextButton>(opt_ref(*horizontal_layout), std::nullopt, sf::Color::Red, "SAVE");
	    save->on_click = [this](const sf::Event&, Button&) {
	    	std::cout << "tba\n";// TODO implement functionality;
	    };
	    horizontal_layout->add(std::move(save));
	    horizontal_layout->setPosition(static_cast<sf::Vector2f>(m_Window.getSize()) - horizontal_layout->getSize());
	m_UI.addLayout(std::move(horizontal_layout));
}

#pragma endregion


/* ==================================      UPDATES      ================================== */


void OptionsState::processEvents(const sf::Event& sfevent)
{
	m_UI.processEvent(sfevent);
}


void OptionsState::update(const sf::Time& deltaTime)
{
	if (m_ShouldQuit)
		m_States.pop();
}


/* ==================================      FUNCTIONS      ================================== */


void OptionsState::readAndApplyButtonData()
{
	std::string results;
	for (auto&& widget : m_UI.getAllWidgets()) {
		if (typeid(*widget).name() == typeid(ArrowSwitchTextButton).name()) {
			auto ptr = dynamic_cast<ArrowSwitchTextButton*>(widget);

			if (ptr->getString() == "Fullscreen") {
				results += "\nfullscreen ";
				results+=(ptr->readValue() == "On" ? "1" : "0");
			}
			else if (ptr->getString() == "Vertical   Synchronization") {
				results += "\nvsync ";
				results += (ptr->readValue() == "On" ? "1" : "0");
			}
			else if (ptr->getString() == "Screen   Resolution") {
				results += "\nresolution " + ptr->readValue();
			}
			else if (ptr->getString() == "Music") {

				auto music = Configuration::m_MainMenuMusic;
				if (ptr->readValue() == "On" && music->getStatus() != sf::Music::Status::Playing) {
					music->play();
				}
				else if (ptr->readValue() == "Off" && music->getStatus() == sf::Music::Status::Playing) {
					music->stop();
				}
			}
			else if (ptr->getString() == "Volume") {
				short int value = (short)std::stoi(ptr->readValue());
				Configuration::m_MasterVolume = value;
				Configuration::m_MainMenuMusic->setVolume(Configuration::m_MasterVolume);
			}
		}
	}

	Helpers::CreateWindow(m_Window, results);
	reposition();
}


void OptionsState::changeResolution(const sf::VideoMode& mode)
{
	if (m_Window.getSize() == sf::Vector2u(mode.width, mode.height))
		return;

	/* READ CONTENTS OF SETTINGS FILE TO REPLACE RESOLUTION VALUES, THEN CREATE WINDOW WITH THESE SETTINGS*/
	std::string file_contents;
	Helpers::LoadFileToString(std::filesystem::path("../media/config/screen.txt"), file_contents);

	std::string x = std::to_string(m_Window.getSize().x);
	std::string y = std::to_string(m_Window.getSize().y);

	Helpers::ReplaceFirstOccurance(file_contents, x, std::to_string(mode.width));
	Helpers::ReplaceFirstOccurance(file_contents, y, std::to_string(mode.height));
		


	std::ofstream settings("../media/config/screen.txt", std::ofstream::out | std::ofstream::trunc);	
	settings << file_contents;
	settings.close();

	Helpers::CreateWindow(m_Window);

	reposition();
}

void OptionsState::goFullscreen(Button& button)
{
	std::string file_contents;
	Helpers::LoadFileToString(std::filesystem::path("../media/config/screen.txt"), file_contents);


	/* I dynamic cast here, but in theory it should not do weird stuff, since only checkbox uses it */
	if (!dynamic_cast<Checkbox*>(&button)->getIsChecked())
		Helpers::ReplaceFirstOccurance(file_contents, "fullscreen 0", "fullscreen 1");
	else
		Helpers::ReplaceFirstOccurance(file_contents, "fullscreen 1", "fullscreen 0");

	
	std::ofstream settings("../media/config/screen.txt", std::ofstream::out | std::ofstream::trunc);	
	settings << file_contents;
	settings.close();


	Helpers::CreateWindow(m_Window);

	reposition();
}

void OptionsState::reposition()
{
	Configuration::m_MainMenu->reposition();

	/* Calculate Background */
	sf::Vector2u win_size = m_Window.getSize();
	sf::Vector2u tex_size = Configuration::m_MainMenu->m_BackgroundTexture.getSize();
	sf::IntRect rect(unsigned(0), (tex_size - win_size).y / (unsigned)2, win_size.x, win_size.y);
	m_BackgroundSprite.setTextureRect(rect);

	/* Calculate Title */
	sf::Vector2f title_position((m_Window.getSize().x - m_Title.getSize().x) / 2.f, 150);
	m_Title.setPosition(title_position);



	/* UI/OPTIONS */
	sf::Vector2f options_layout_pos;
	options_layout_pos.x = (static_cast<float>(m_Window.getSize().x) - m_UI.getLayoutAtIndex((int)LayoutIndexes::graphics)->getSize().x) / 2.f;
	options_layout_pos.y = m_Title.getPosition().y + m_Title.getSize().y + 50.f;
	m_UI.setPositionAtIndex(options_layout_pos, (int)LayoutIndexes::graphics);


	/* UI/NAVIGATION*/
	sf::Vector2f navi_layout_pos(static_cast<sf::Vector2f>(m_Window.getSize()) - m_UI.getLayoutAtIndex((int)LayoutIndexes::navigation)->getSize());
	m_UI.setPositionAtIndex(navi_layout_pos, (int)LayoutIndexes::navigation);

}


void OptionsState::flipMusicState()
{
	if (Configuration::m_MainMenuMusic->getStatus() == sf::Sound::Status::Playing)
		Configuration::m_MainMenuMusic->pause();
	else
		Configuration::m_MainMenuMusic->play();
}
