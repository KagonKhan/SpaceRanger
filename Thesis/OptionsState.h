#pragma once
#include "State.h"
#include "MainMenuState.h"


class OptionsState : public State
{
	enum UITypes : int {Resolutions, Music, Navigation };
	std::unordered_map<int, UI*> uis;
	Label m_Title;

	sf::Sprite& m_BackgroundSprite;

	void initGUI();
		void initGUIResolutions();
		void initGUIMusic();
		void initGUINavigation();

	void initTitle();

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override final;


	void goFullscreen(Button& button);
	void flipMusicState();
	void changeResolution(const sf::VideoMode& mode);
	void recalculatePositions();
public:

	void processEvents(const sf::Event& sfevent);
	OptionsState(sf::RenderWindow& window, std::stack<State*>& states, sf::Sprite& bgsprite);
	~OptionsState();


	void update(const sf::Time& deltaTime) override final;
};