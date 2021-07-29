#include "MainMenuState.h"
#include <iostream>


MainMenuState::MainMenuState(sf::RenderWindow& window, std::stack<State*>& states)
	: State(window, states), ui(window), m_BackgroundTexture(Configuration::background_textures.get(Configuration::Backgrounds::MainMenu))
{
	initGUI();
	initBackground();
}

MainMenuState::~MainMenuState()
{

}


void MainMenuState::initGUI()
{
	VerticalLayout* layout = new VerticalLayout;
	TextButton* button = new TextButton("New Game");
	TextButton* button2 = new TextButton("Options");
	button->on_click = [this](const sf::Event&, Button& button) {
		std::cout << "New Game\n";
	};

	button2->on_click = [this](const sf::Event&, Button& button) {
		std::cout << "Options\n";
	};


	layout->add(button);
	layout->add(button2);

	ui.addLayout(layout);

	ui.bind(
		Configuration::GuiInputs::Escape,
		[this](const sf::Event& sfevent)
		{
			this->m_Window.close();
		}
	);

	ui.bind(
		Configuration::GuiInputs::N,
		[this](const sf::Event& sfevent)
		{
			std::cout << "New Game\n";
		}
	);

	ui.bind(
		Configuration::GuiInputs::O,
		[this](const sf::Event& sfevent)
		{
			std::cout << "Options\n";
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

void MainMenuState::updateBackground(const sf::Time& deltaTime)
{
	static bool move_right = true;
	static sf::Vector2u tex_size = m_BackgroundSprite.getTexture()->getSize();
	static sf::Vector2u win_size = m_Window.getSize();

	/* Slow down movement */
	static float move_by = 0;
	move_by += 20 * deltaTime.asSeconds();


	sf::IntRect rect = m_BackgroundSprite.getTextureRect();
	std::cout << rect.left << " " << win_size.x << " " << tex_size.x << "\n";
		 
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

void MainMenuState::processEvents(const sf::Event& sfevent)
{
	ui.processEvent(sfevent);
}



void MainMenuState::update(const sf::Time& deltaTime)
{
	updateBackground(deltaTime);
}




void MainMenuState::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_BackgroundSprite);
	target.draw(ui);
}

void MainMenuState::Options()
{
	m_States.emplace(std::move(new OptionsState(m_Window, m_States)));
}

void MainMenuState::NewGame()
{
	m_States.emplace(std::move(new SpaceState(m_Window, m_States)));
}

