#include "pch.h"
#include "MainMenuState.h"
#include "HangarState.h"

#include "OptionsState.h"
void MainMenuState::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_BackgroundSprite);
	target.draw(m_Title);
	target.draw(m_UI);
}


MainMenuState::MainMenuState(sf::RenderWindow& window, std::stack<State*>& states)
	: State(window, states),
	m_BackgroundTexture(Configuration::background_textures.get(Configuration::Backgrounds::MainMenu)),
	m_Title(std::nullopt,"SPACE RANGER", Configuration::fonts.get(Configuration::Fonts::SpaceGui))
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
	m_States.pop();
}


void MainMenuState::initGUI()
{
	std::unique_ptr<VerticalLayout> layout(new VerticalLayout(opt_ref(m_UI), 2.f));

	std::unique_ptr<TextButton> new_game(new TextButton(opt_ref(*layout), std::nullopt, sf::Color::Red, "(N)ew Game"));
	new_game->setLetterSpacing(5);
	new_game->on_click = [this](const sf::Event&, Button&) {
		NewGame();
	};

	std::unique_ptr<TextButton> options(new TextButton(opt_ref(*layout), std::nullopt, sf::Color::Red, "(O)ptions"));
	options->setLetterSpacing(5);
	options->on_click = [this](const sf::Event&, Button&) {
		Options();
	};
	
	std::unique_ptr<TextButton> high_scores(new TextButton(opt_ref(*layout), std::nullopt, sf::Color::Red, "(H)ight Scores"));
	high_scores->setLetterSpacing(5);
	high_scores->on_click = [this](const sf::Event&, Button&) {
		std::cout << "High Scores\n";
	};	

	std::unique_ptr<TextButton> quit(new TextButton(opt_ref(*layout), std::nullopt, sf::Color::Red, "(Q)uit"));
	quit->setLetterSpacing(5);
	quit->on_click = [this](const sf::Event&, Button&) {
		delete this;
	};


	layout->add(std::move(new_game));
	layout->add(std::move(options));
	layout->add(std::move(high_scores));
	layout->add(std::move(quit));


	layout->setPosition(sf::Vector2f(m_Window.getSize()) / 2.f);

	m_UI.addLayout(std::move(layout));

	m_UI.bind( Configuration::GuiInputs::N,
		[this](const sf::Event& sfevent)
		{
			std::cout << "New Game\n";
		}
	);

	m_UI.bind( Configuration::GuiInputs::O,
		[this](const sf::Event& sfevent)
		{
			std::cout << "Options\n";
		}
	);

	m_UI.bind( Configuration::GuiInputs::H,
		[this](const sf::Event& sfevent)
		{
			std::cout << "High Scores\n";
		}
	);

	m_UI.bind( Configuration::GuiInputs::Escape,
		[this](const sf::Event& sfevent)
		{
			this->m_Window.close();
		}
	);

	m_UI.bind( Configuration::GuiInputs::Q,
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
	Configuration::m_MainMenuMusic = &Configuration::musics.get(Configuration::Musics::MainMenuTheme);
	Configuration::m_MainMenuMusic->setAttenuation(0);
	Configuration::m_MainMenuMusic->setLoop(true);
	Configuration::m_MainMenuMusic->setVolume(5);
	Configuration::m_MainMenuMusic->play();
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

	static auto is_in_range = [](int val, int lower, int upper)	{
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
	else {
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
	m_UI.processEvent(sfevent);
}


void MainMenuState::update(const sf::Time& deltaTime)
{
	updateBackground(deltaTime);
	updateTitle(deltaTime);
}


void MainMenuState::Options()
{
	m_States.push(Configuration::m_Options);
}

void MainMenuState::NewGame()
{
	Configuration::m_MainMenuMusic->stop();
	m_States.push(new HangarState(m_Window, m_States));
}

void MainMenuState::reposition()
{
	

	sf::Vector2u win_size = m_Window.getSize();
	sf::Vector2u tex_size = m_BackgroundTexture.getSize();
	sf::IntRect rect(unsigned(0), (tex_size - win_size).y / (unsigned)2, win_size.x, win_size.y);
	m_BackgroundSprite.setTextureRect(rect);


	sf::Vector2f title_position((m_Window.getSize().x - m_Title.getSize().x) / 2.f, 150);

	m_Title.setPosition(title_position);


	m_UI.setPositionAtIndex(sf::Vector2f(m_Window.getSize()) / 2.f, 0);
}

