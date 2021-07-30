#pragma once
#include "State.h"
#include "SpaceState.h"
#include "OptionsState.h"

class MainMenuState: public State
{
	friend class OptionsState;
	UI ui;
	Label m_Title;
	
	sf::Texture& m_BackgroundTexture;
	sf::Sprite m_BackgroundSprite;
	sf::Music* m_MainMenuMusic;

	void initGUI();
	void initBackground();
	void initTitle();
	void initMusic();

	void updateBackground(const sf::Time& deltaTime);
	void updateTitle(const sf::Time& deltaTime);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override final;

	void Options();
	void NewGame();

	void recalculatePositions();

public:
	friend class OptionsState;
	void processEvents(const sf::Event& sfevent);
	MainMenuState(sf::RenderWindow& window, std::stack<State*>& states);
	~MainMenuState();


	void update(const sf::Time& deltaTime)  override final;
};

