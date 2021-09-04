#pragma once
#include "State.h"
#include "MainMenuState.h"


class OptionsState :
	public State
{

	UserInterface m_UI;
	Label m_Title;

	sf::Sprite& m_BackgroundSprite;

	void initGUI();
		void initGUIResolutions();
		void initGUIMusic();
		void initGUINavigation();

	void initTitle();

	void draw(sf::RenderTarget& target, sf::RenderStates) const override final;


	void goFullscreen(Button& button);
	void flipMusicState();
	void changeResolution(const sf::VideoMode& mode);
	void reposition();
public:

	OptionsState(sf::RenderWindow& window, std::stack<State*>& states, sf::Sprite& bgsprite);
	virtual ~OptionsState();


	void processEvents(const sf::Event& sfevent);

	void update(const sf::Time& deltaTime) override final;
};