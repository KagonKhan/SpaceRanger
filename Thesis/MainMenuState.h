#pragma once
#include "State.h"
#include "SpaceState.h"
#include "OptionsState.h"

class MainMenuState: public State
{
	UI ui;
	sf::Texture& m_BackgroundTexture;
	sf::Sprite m_BackgroundSprite;

	void initGUI();
	void initBackground();

	void updateBackground(const sf::Time& deltaTime);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override final;

	void Options();
	void NewGame();
public:

	void processEvents(const sf::Event& sfevent);
	MainMenuState(sf::RenderWindow& window, std::stack<State*>& states);
	~MainMenuState();


	void update(const sf::Time& deltaTime)  override final;
};

