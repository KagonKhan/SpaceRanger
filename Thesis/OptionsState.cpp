#include "pch.h"
#include "OptionsState.h"
#include "MainMenuState.h"

void OptionsState::draw(sf::RenderTarget& target, sf::RenderStates) const
{
	target.draw(m_BackgroundSprite);
	target.draw(m_Title);
	target.draw(m_UI);
}

OptionsState::OptionsState(sf::RenderWindow& window, std::stack<State*>& states, sf::Sprite& bgsprite)
	: State(window, states), m_BackgroundSprite(bgsprite), 
	m_Title(std::nullopt,"OPTIONS", Configuration::fonts.get(Configuration::Fonts::SpaceGui), 100)
{
	puts("OptionsState\tctor");
	initTitle();
	initGUI();
}

OptionsState::~OptionsState()
{
	puts("OptionsState\tdtor");
}


/* ==================================      INITIALIZERS      ================================== */


void OptionsState::initTitle()
{
	m_Title.setLetterSpacing(8);
	m_Title.setOutlineThickness(9);
	m_Title.setOutlineColor(sf::Color::Blue);
	sf::Vector2f title_position((m_Window.getSize().x - m_Title.getSize().x) / 2.f, 150);

	m_Title.setPosition(title_position);

}

void OptionsState::initGUI()
{
	addGUIGraphics();

	initGUIMusic();

	addGUINavigation();
}

#pragma region GUI/Graphics

void OptionsState::addGUIGraphics()
{
	VerLayPtr vert_layout(new VerticalLayout(opt_ref(m_UI), 5.f));
		addButtonResolutions(vert_layout);
		addButtonFullscreen(vert_layout);
		addButtonVSync(vert_layout);
	m_UI.addLayout(std::move(vert_layout));
}
void OptionsState::addButtonResolutions(VerLayPtr& vert_layout)
{
	std::vector<sf::VideoMode> modes = sf::VideoMode::getFullscreenModes();

	sf::Vector2f size(m_Window.getSize().x * 0.8f, 75.f);
	std::string	button_text = "Screen   Resolution";
	sf::Font& font = Configuration::fonts.get(Configuration::Fonts::SpaceGui);
	sf::Vector2f area_size(500.f, 75.f);

	std::unique_ptr<ArrowSwitchTextButton> window_sizes(new ArrowSwitchTextButton(
		opt_ref(m_UI), size, button_text, font, 25u, modes.size(), area_size, sf::Vector2f(100, 50)));

	for (unsigned int i = 0; i < modes.size(); ++i) {
		std::string	button_text = std::to_string(modes[i].width) + "   x   " + std::to_string(modes[i].height);
		window_sizes->addOption(button_text, font, 25u);
	}

	vert_layout->add(std::move(window_sizes));


	sf::Vector2f layout_pos;
	layout_pos.x = (static_cast<float>(m_Window.getSize().x) - vert_layout->getSize().x) / 2.f;
	layout_pos.y = m_Title.getPosition().y + m_Title.getSize().y + 50.f;
	vert_layout->setPosition(layout_pos);


}
void OptionsState::addButtonFullscreen(VerLayPtr& vert_layout)
{
	sf::Vector2f size(m_Window.getSize().x * 0.8f, 75.f);
	sf::Font& font = Configuration::fonts.get(Configuration::Fonts::SpaceGui);
	sf::Vector2f area_size(500.f, 75.f);

	std::unique_ptr<ArrowSwitchTextButton> fullscreen(new ArrowSwitchTextButton(
		opt_ref(m_UI), size, "Fullscreen", font, 25u, 2, area_size, sf::Vector2f(100, 50)));
	fullscreen->addOption("On", font, 25u);
	fullscreen->addOption("Off", font, 25u);

	vert_layout->add(std::move(fullscreen));
}
void OptionsState::addButtonVSync(VerLayPtr& vert_layout)
{
	sf::Vector2f size(m_Window.getSize().x * 0.8f, 75.f);
	sf::Font& font = Configuration::fonts.get(Configuration::Fonts::SpaceGui);
	sf::Vector2f area_size(500.f, 75.f);

	std::unique_ptr<ArrowSwitchTextButton> vsync(new ArrowSwitchTextButton(
		opt_ref(m_UI), size, "Vertical   Synchronization", font, 25u, 2, area_size, sf::Vector2f(100, 50)));
	vsync->addOption("On", font, 25u);
	vsync->addOption("Off", font, 25u);


	vert_layout->add(std::move(vsync));
}

#pragma endregion

void OptionsState::initGUIMusic()
{
	//uis.insert(std::make_pair<int, UI*>(Music, new UI(m_Window)));

	//HorizontalLayout* music_buttons = new HorizontalLayout();

	//Checkbox* music_checkbox = new Checkbox("Music");
	//music_checkbox->on_click = [this](const sf::Event&, Button& button) {
	//	flipMusicState();
	//};

	//TextButton* music_slider = new TextButton("THIS WILL BE A MUSIC SLIDER");
	//music_slider->on_click = [this](const sf::Event&, Button& button) {
	//	//TODO: slider implementation();
	//};
	//music_checkbox->setIsChecked(true);

	//music_buttons->add(music_checkbox);
	//music_buttons->add(music_slider);
	//music_buttons->setPosition(sf::Vector2f(50, 400));

	//uis.at(Music)->addLayout(music_buttons);
}

#pragma region GUI/navigation

void OptionsState::addGUINavigation()
{
	UnoLayPtr unordered_layout(new UnorderedLayout(opt_ref(m_UI)));
		addButtonBack(unordered_layout);
	m_UI.addLayout(std::move(unordered_layout));

	HorLayPtr horizontal_layout(new HorizontalLayout(opt_ref(m_UI), 5.f));
		addButtonApply(horizontal_layout);
		addButtonSave(horizontal_layout);
	horizontal_layout->setPosition(static_cast<sf::Vector2f>(m_Window.getSize()) - horizontal_layout->getSize());
	m_UI.addLayout(std::move(horizontal_layout));
}

void OptionsState::addButtonBack(UnoLayPtr& unordered_layout)
{
	std::unique_ptr<TextButton> back(new TextButton(
		opt_ref(*unordered_layout), std::nullopt, sf::Color::Red, "BACK"));
	back->on_click = [this](const sf::Event&, Button&) {
		m_States.pop();
	};
	back->setPosition(sf::Vector2f(0, 0));

	unordered_layout->add(std::move(back));
}

void OptionsState::addButtonApply(HorLayPtr& horizontal_layout)
{
	std::unique_ptr<TextButton> save(new TextButton(
		opt_ref(*horizontal_layout), std::nullopt, sf::Color::Red, "APPLY"));
	save->on_click = [this](const sf::Event&, Button& button) {
		readAndApplyButtonData();
	};
	horizontal_layout->add(std::move(save));
}

void OptionsState::addButtonSave(HorLayPtr& horizontal_layout)
{
	std::unique_ptr<TextButton> save(new TextButton(
		opt_ref(*horizontal_layout), std::nullopt, sf::Color::Red, "SAVE"));
	save->on_click = [this](const sf::Event&, Button& button) {
		std::cout << "tba\n";// TODO implement functionality;
	};
	horizontal_layout->add(std::move(save));
}

#pragma endregion


/* ==================================      UPDATES      ================================== */


void OptionsState::processEvents(const sf::Event& sfevent)
{
	m_UI.processEvent(sfevent);
}


void OptionsState::update(const sf::Time& deltaTime)
{
	
}


/* ==================================      FUNCTIONS      ================================== */


void OptionsState::readAndApplyButtonData()
{

	std::string results;
	auto widgets = m_UI.getAllWidgets();
	for (auto&& widget : widgets) {
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
		}
	}
	system("CLS");
	std::cout << results;
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

}


void OptionsState::flipMusicState()
{
	if (Configuration::m_MainMenuMusic->getStatus() == sf::Sound::Status::Playing)
		Configuration::m_MainMenuMusic->pause();
	else
		Configuration::m_MainMenuMusic->play();
}
