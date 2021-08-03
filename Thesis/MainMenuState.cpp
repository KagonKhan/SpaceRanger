#include "pch.h"
#include "MainMenuState.h"
#include "HangarState.h"

MainMenuState::MainMenuState(sf::RenderWindow& window, std::stack<State*>& states)
	: State(window, states), ui(window),
	m_BackgroundTexture(Configuration::background_textures.get(Configuration::Backgrounds::MainMenu)),
	m_Title("SPACE RANGER")
	
{
	initGUI();
	initBackground();
	initTitle();
	initMusic();

	Configuration::m_Options = new OptionsState(m_Window, m_States, m_BackgroundSprite);
	Configuration::m_MainMenu = this;
}

MainMenuState::~MainMenuState()
{

}


void MainMenuState::initGUI()
{
	VerticalLayout* layout = new VerticalLayout;

	TextButton* new_game = new TextButton("(N)ew Game");
	new_game->setLetterSpacing(5);
	new_game->on_click = [this](const sf::Event&, Button& button) {
		NewGame();
	};

	TextButton* options = new TextButton("(O)ptions");
	options->setLetterSpacing(5);
	options->on_click = [this](const sf::Event&, Button& button) {
		Options();
	};
	
	TextButton* high_scores = new TextButton("(H)igh Scores");
	high_scores->setLetterSpacing(5);
	high_scores->on_click = [this](const sf::Event&, Button& button) {
		std::cout << "High Scores\n";
	};	

	TextButton* quit = new TextButton("(Q)uit");
	quit->setLetterSpacing(5);
	quit->on_click = [this](const sf::Event&, Button& button) {
		m_Window.close();
	};

	layout->add(new_game);
	layout->add(options);
	layout->add(high_scores);
	layout->add(quit);

	layout->setPosition(sf::Vector2f(m_Window.getSize()) / 2.f);

	ui.addLayout(layout);

	ui.bind( Configuration::GuiInputs::N,
		[this](const sf::Event& sfevent)
		{
			std::cout << "New Game\n";
		}
	);

	ui.bind( Configuration::GuiInputs::O,
		[this](const sf::Event& sfevent)
		{
			std::cout << "Options\n";
		}
	);

	ui.bind( Configuration::GuiInputs::H,
		[this](const sf::Event& sfevent)
		{
			std::cout << "High Scores\n";
		}
	);

	ui.bind( Configuration::GuiInputs::Escape,
		[this](const sf::Event& sfevent)
		{
			this->m_Window.close();
		}
	);

	ui.bind( Configuration::GuiInputs::Q,
		[this](const sf::Event& sfevent)
		{
			this->m_Window.close();
		}
	);
}

void MainMenuState::initBackground()
{
	m_BackgroundSprite.setTexture(m_BackgroundTexture);

	sf::Vector2u win_size = m_Window.getSize();
	sf::Vector2u tex_size = m_BackgroundTexture.getSize();
	sf::IntRect rect(unsigned(0), (tex_size - win_size).y / (unsigned)2, win_size.x, win_size.y);
	m_BackgroundSprite.setTextureRect(rect);
}

void MainMenuState::initTitle()
{
	m_Title.setCharacterSize(100);
	m_Title.setLetterSpacing(8);
	m_Title.setOutlineThickness(9);
	m_Title.setOutlineColor(sf::Color::Blue);
	sf::Vector2f title_position((m_Window.getSize().x - m_Title.getSize().x) / 2.f, 150);

	m_Title.setPosition(title_position);
}

void MainMenuState::initMusic()
{
	m_MainMenuMusic = &Configuration::musics.get(Configuration::Musics::MainMenuTheme);
	m_MainMenuMusic->setAttenuation(0);
	m_MainMenuMusic->setLoop(true);
	m_MainMenuMusic->setVolume(5);
	m_MainMenuMusic->play();
}

void MainMenuState::updateBackground(const sf::Time& deltaTime)
{
	static bool move_right = true;
	static sf::Vector2u tex_size = m_BackgroundSprite.getTexture()->getSize();
	static sf::Vector2u win_size = m_Window.getSize();

	/* Slow down movement */
	static float move_by = 0;
	move_by += 20 * deltaTime.asSeconds();


	sf::IntRect rect = m_BackgroundSprite.getTextureRect();
		 
	if (move_right) {
		if (rect.left + win_size.x < tex_size.x) {
			if (move_by >= 1) {
				rect.left += 1;
				move_by -= 1;
			}
		}
		else 
			move_right = !move_right;	
	}
	else {
		if (rect.left > 0) {
			if (move_by >= 1) {
				rect.left -= 1;
				move_by -= 1;
			}
		}
		else
			move_right = !move_right;
	}

	m_BackgroundSprite.setTextureRect(rect);
}

void MainMenuState::updateTitle(const sf::Time& deltaTime)
{
	static bool move_up = true;
	static const sf::Color tit_col = m_Title.getOutlineColor(); 

	static auto is_in_range = [](int val, int lower, int upper)
	{
		return lower <= val && val <= upper;
	};

	/* Current title color */
	sf::Color ctc= m_Title.getOutlineColor();
	if (move_up) {
		if (is_in_range(ctc.r, 0, 253)) {
			ctc.r += 1;
		}
		else
			move_up = !move_up;
	}
	else
	{
		if (is_in_range(ctc.r, 1, 254)) {
			ctc.r -= 1;
		}
		else
			move_up = !move_up;
	}

	m_Title.setOutlineColor(ctc);
}

void MainMenuState::processEvents(const sf::Event& sfevent)
{
	ui.processEvent(sfevent);
}


void MainMenuState::update(const sf::Time& deltaTime)
{
	updateBackground(deltaTime);
	updateTitle(deltaTime);
}


void MainMenuState::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_BackgroundSprite);
	target.draw(m_Title);
	target.draw(ui);
}

void MainMenuState::Options()
{
	m_States.push(Configuration::m_Options);
}

void MainMenuState::NewGame()
{
	m_States.push(new HangarState(m_Window, m_States));
}

void MainMenuState::recalculatePositions()
{

	sf::Vector2u win_size = m_Window.getSize();
	sf::Vector2u tex_size = m_BackgroundTexture.getSize();
	sf::IntRect rect(unsigned(0), (tex_size - win_size).y / (unsigned)2, win_size.x, win_size.y);
	m_BackgroundSprite.setTextureRect(rect);


	sf::Vector2f title_position((m_Window.getSize().x - m_Title.getSize().x) / 2.f, 150);

	m_Title.setPosition(title_position);


	ui.setLayoutPosition(sf::Vector2f(m_Window.getSize()) / 2.f);
}

