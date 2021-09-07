#pragma once
#include "SpaceState.h"


class MainMenuState :
	public State
{
friend class OptionsState;
private:
	UserInterface m_UI;
	Label m_Title;
	
	sf::Texture& m_BackgroundTexture;
	sf::Sprite m_BackgroundSprite;


	void initTitle();
	void initGUI();
	void initBackground();
	void initMusic();


	void updateBackground(const sf::Time& deltaTime);
	void updateTitle(const sf::Time& deltaTime);

	void draw(sf::RenderTarget& target, sf::RenderStates) const override final;

	void Options();
	void NewGame();

	void reposition();

public:
	MainMenuState(sf::RenderWindow& window, std::stack<State::ptr>& states);
	virtual ~MainMenuState();

	void processEvents(const sf::Event& sfevent);

	void update(const sf::Time& deltaTime)  override final;
};

