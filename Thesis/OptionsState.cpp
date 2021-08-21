#include "pch.h"
#include "OptionsState.h"


void OptionsState::processEvents(const sf::Event& sfevent)
{
	for (UI* ui : uis)
		ui->processEvent(sfevent);
}

OptionsState::OptionsState(sf::RenderWindow& window, std::stack<State*>& states, sf::Sprite& bgsprite)
	: State(window, states), m_BackgroundSprite(bgsprite), 
	m_Title("OPTIONS")
{
	std::cout << "\nOptions State constructor\n";
	initGUI();
	initTitle();
}

OptionsState::~OptionsState()
{
	std::cout << "\nOptions State destructor\n";
}


void OptionsState::initGUI()
{
	uis.reserve(3);
		initGUIResolutions();
		initGUIMusic();
		initGUINavigation();

	/*
	/* TODO: Clean up the code
	VerticalScrollingLayout* vert_layout = new VerticalScrollingLayout;

	std::vector<sf::VideoMode> modes = sf::VideoMode::getFullscreenModes();
	int index;
	for (int i = 0; i < modes.size(); ++i) {

		std::string	button_text = std::to_string(modes[i].width) + "   x   " + std::to_string(modes[i].height);
		TextButton* button = new TextButton(button_text);
		button->setSize(sf::Vector2f(250, 75));

		button->on_click = [this](const sf::Event&, Button& button) {
			ui.showAllButtons();
			std::cout << "test";
			//activateButton(&button);
		};

		button->setID(i);

		

		/* Set only this as visible 
		if (m_Window.getSize().x == modes[i].width && m_Window.getSize().y == modes[i].height) {
			button->setIsVisible(true);
			button->setIsActive(true);
			index = i;
		}
		else {
			button->setIsVisible(false);
			button->setIsActive(false);
		}
		vert_layout->add(button);
	}
	sf::Vector2f pos(300, 200);
	vert_layout->setPosition(pos);


	pos.y -= index*75;
	vert_layout->setPosition(pos);

	scrollUI.addLayout(vert_layout);
	*/
}

void OptionsState::initGUIResolutions()
{
	uis.push_back(new UI(m_Window));
		HorizontalLayout* window_sizes = new HorizontalLayout();


	std::vector<sf::VideoMode> modes = sf::VideoMode::getFullscreenModes();

	for (int i = 0; (i <= modes.size()) && (i <= 4); i += 2) {
		std::string	button_text = std::to_string(modes[i].width) + "   x   " + std::to_string(modes[i].height);
		TextButton* button = new TextButton(button_text);
		button->setSize(sf::Vector2f(250, 75));

		button->on_click = [i, modes, this](const sf::Event&, Button& button) {
			changeResolution(modes[i]);
		};

		window_sizes->add(button);
	}

	Checkbox* fullscreen = new Checkbox("Fullscreen");
	fullscreen->setSize(sf::Vector2f(300, 75));
	fullscreen->on_click = [this](const sf::Event&, Button& button) {
		goFullscreen(button);
	};

	sf::Vector2u max_win_size(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height);
	fullscreen->setIsChecked(m_Window.getSize() == max_win_size);



	window_sizes->add(fullscreen);
	window_sizes->setPosition(sf::Vector2f(50, 300));
	uis.back()->addLayout(window_sizes);
}

void OptionsState::initGUIMusic()
{
	uis.push_back(new UI(m_Window));

	HorizontalLayout* music_buttons = new HorizontalLayout();

	Checkbox* music_checkbox = new Checkbox("Music");
	music_checkbox->on_click = [this](const sf::Event&, Button& button) {
		flipMusicState();
	};
	music_checkbox->setIsChecked(true);
	music_checkbox->setPosition(sf::Vector2f(50, 400));
	music_buttons->add(music_checkbox);

	uis.back()->addLayout(music_buttons);
	uis.back()->setPosition(sf::Vector2f(50, 400));
}

void OptionsState::initGUINavigation()
{
	uis.push_back(new UI(m_Window));

	VerticalLayout* navigation = new VerticalLayout;
	TextButton* back = new TextButton("BACK");
	back->on_click = [this](const sf::Event&, Button& button) {
		m_States.pop();
	};


	navigation->add(back);
	navigation->setPosition(sf::Vector2f(0, 0));
	uis.back()->addLayout(navigation);
	uis.back()->setPosition(sf::Vector2f(0, 0));
}






void OptionsState::initTitle()
{
	m_Title.setCharacterSize(100);
	m_Title.setLetterSpacing(8);
	m_Title.setOutlineThickness(9);
	m_Title.setOutlineColor(sf::Color::Blue);
	sf::Vector2f title_position((m_Window.getSize().x - m_Title.getSize().x) / 2.f, 150);

	m_Title.setPosition(title_position);

}

void OptionsState::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_BackgroundSprite);
	target.draw(m_Title);

	for(UI* ui : uis)
		target.draw(*ui);

}

void OptionsState::update(const sf::Time& deltaTime)
{
	
}

/* TODO: FIX THIS, it's so stupid, normalize the functionality */

void OptionsState::recalculatePositions(UI* ui, const sf::Vector2f &pos)
{
	Configuration::m_MainMenu->m_BackgroundTexture;

	sf::Vector2u win_size = m_Window.getSize();
	sf::Vector2u tex_size = Configuration::m_MainMenu->m_BackgroundTexture.getSize();
	sf::IntRect rect(unsigned(0), (tex_size - win_size).y / (unsigned)2, win_size.x, win_size.y);
	m_BackgroundSprite.setTextureRect(rect);


	sf::Vector2f title_position((m_Window.getSize().x - m_Title.getSize().x) / 2.f, 150);

	uis[0]->setPosition(pos);
	
	uis[2]->setPosition(sf::Vector2f(0, 0));
	m_Title.setPosition(title_position);

}

/* When creating a new window, which is how to resize the window, the settings like framerate limit get nuked */
void OptionsState::changeResolution(const sf::VideoMode& mode)
{
	if (m_Window.getSize() == sf::Vector2u(mode.width, mode.height))
		return;


	/* READ CONTENTS OF SETTINGS FILE TO REPLACE RESOLUTION VALUES, THEN CREATE WINDOW WITH THESE SETTINGS*/
	std::string file_contents;
	Configuration::LoadFileToString(std::filesystem::path("../media/config/screen.txt"), file_contents);

	std::string x = std::to_string(m_Window.getSize().x);
	std::string y = std::to_string(m_Window.getSize().y);

	Configuration::ReplaceFirstOccurance(file_contents, x, std::to_string(mode.width));
	Configuration::ReplaceFirstOccurance(file_contents, y, std::to_string(mode.height));
		


	std::ofstream settings("../media/config/screen.txt", std::ofstream::out | std::ofstream::trunc);	
	settings << file_contents;
	settings.close();

	Configuration::CreateWindow(m_Window);















	Configuration::m_MainMenu->recalculatePositions();
	recalculatePositions(uis[0], sf::Vector2f(50,300));
	uis[1]->setPosition(sf::Vector2f(uis[0]->getPosition().x, uis[0]->getPosition().y + uis[0]->getSize().y));

	std::vector<Widget*> widgets = uis[0]->getWidgets();
	/* TURN OFF THE CHECK ON FULLSCREEN CHECKBOX BUTTON, KINGA GARBE - IDK HOW SLOW THIS IS FOR NOW */
	for (Widget* widget : widgets) 
		if (typeid(*widget).name() == typeid(Checkbox).name())
			dynamic_cast<Checkbox*>(widget)->setIsChecked(false);
	
}

void OptionsState::goFullscreen(Button& button)
{
	std::string file_contents;
	Configuration::LoadFileToString(std::filesystem::path("../media/config/screen.txt"), file_contents);


	/* I dynamic cast here, but in theory it should not do weird stuff, since only checkbox uses it */
	if (!dynamic_cast<Checkbox*>(&button)->getIsChecked())
		Configuration::ReplaceFirstOccurance(file_contents, "fullscreen 0", "fullscreen 1");
	else
		Configuration::ReplaceFirstOccurance(file_contents, "fullscreen 1", "fullscreen 0");


	std::ofstream settings("../media/config/screen.txt", std::ofstream::out | std::ofstream::trunc);
	settings << file_contents;
	settings.close();


	Configuration::CreateWindow(m_Window);

	Configuration::m_MainMenu->recalculatePositions();
	recalculatePositions(uis[0], sf::Vector2f(50, 300));
}

void OptionsState::flipMusicState()
{
	if (Configuration::m_MainMenuMusic->getStatus() == sf::Sound::Status::Playing)
		Configuration::m_MainMenuMusic->pause();
	else
		Configuration::m_MainMenuMusic->play();
}
