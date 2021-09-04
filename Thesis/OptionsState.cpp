#include "pch.h"
#include "OptionsState.h"


void OptionsState::draw(sf::RenderTarget& target, sf::RenderStates) const
{
	target.draw(m_BackgroundSprite);
	target.draw(m_Title);
	target.draw(m_UI);
}

OptionsState::OptionsState(sf::RenderWindow& window, std::stack<State*>& states, sf::Sprite& bgsprite)
	: State(window, states), m_BackgroundSprite(bgsprite), 
	m_Title(std::nullopt,"OPTIONS", Configuration::fonts.get(Configuration::Fonts::SpaceGui))
{
	puts("OptionsState\tctor");
	initTitle();
	initGUI();
}

OptionsState::~OptionsState()
{
	puts("OptionsState\tdtor");
}


void OptionsState::initGUI()
{
	initGUIResolutions();
	initGUIMusic();
	initGUINavigation();

}

void OptionsState::initGUIResolutions()
{
	std::unique_ptr<VerticalLayout> vert_layout(new VerticalLayout(opt_ref(m_UI), 5.f));

	std::vector<sf::VideoMode> modes = sf::VideoMode::getFullscreenModes();


	sf::Vector2f size(m_Window.getSize().x * 0.8f, 75.f);
	std::string	button_text = "Screen Resolution";
	sf::Font& font = Configuration::fonts.get(Configuration::Fonts::SpaceGui);
	sf::Vector2f area_size(500.f, 75.f);


	std::unique_ptr<ArrowSwitchTextButton> window_sizes(new ArrowSwitchTextButton(
		opt_ref(m_UI), size, button_text, font, 25u, modes.size(), area_size, sf::Vector2f(100,50)));


	for (int i = 0; i < modes.size(); ++i) {
		std::string	button_text = std::to_string(modes[i].width) + "   x   " + std::to_string(modes[i].height);
		window_sizes->addOption(button_text, font, 25u);
	}

	vert_layout->add(std::move(window_sizes));

	sf::Vector2f layout_pos;
	layout_pos.x = (static_cast<float>(m_Window.getSize().x) - vert_layout->getSize().x) / 2.f;
	layout_pos.y = m_Title.getPosition().y + m_Title.getSize().y + 50.f;
	vert_layout->setPosition(layout_pos);

	m_UI.addLayout(std::move(vert_layout));


	//Checkbox* fullscreen = new Checkbox("Fullscreen");
	//fullscreen->setSize(sf::Vector2f(300, 75));
	//fullscreen->on_click = [this](const sf::Event&, Button& button) {
	//	goFullscreen(button);
	//};

	//sf::Vector2u max_win_size(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height);
	//fullscreen->setIsChecked(m_Window.getSize() == max_win_size);



	//window_sizes->add(fullscreen);
	//window_sizes->setPosition(sf::Vector2f(50, 300));
	//uis.at(Resolutions)->addLayout(window_sizes);
}

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

void OptionsState::initGUINavigation()
{
	//uis.insert(std::make_pair<int, UI*>(Navigation, new UI(m_Window)));

	//HorizontalLayout* navigation = new HorizontalLayout;
	//TextButton* back = new TextButton("BACK");
	//back->on_click = [this](const sf::Event&, Button& button) {
	//	m_States.pop();
	//};

	//TextButton* save = new TextButton("SAVE");
	//save->on_click = [this](const sf::Event&, Button& button) {
	//	std::cout << "tba\n";// TODO implement functionality;
	//};

	//navigation->add(back);
	//navigation->add(save);
	//navigation->setPosition(sf::Vector2f(0, 0));
	//save->setPosition(sf::Vector2f(m_Window.getSize()) - save->getSize());
	//uis.at(Navigation)->addLayout(navigation);
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


void OptionsState::processEvents(const sf::Event& sfevent)
{
	m_UI.processEvent(sfevent);
}

void OptionsState::update(const sf::Time& deltaTime)
{
	
}



/* When creating a new window, which is how to resize the window, the settings like framerate limit get nuked */
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
