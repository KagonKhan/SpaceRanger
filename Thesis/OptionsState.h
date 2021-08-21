#pragma once
#include "State.h"
#include "MainMenuState.h"


class OptionsState : public State
{

	std::vector<UI*> uis;
	Label m_Title;

	sf::Sprite& m_BackgroundSprite;

	void initGUI();

	void initTitle();

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override final;


	void fullscreen(Button& button);
	void flipMusicState();
	void changeResolution(const sf::VideoMode& mode);
	void recalculatePositions(UI* ui, const sf::Vector2f &pos);
public:

	void processEvents(const sf::Event& sfevent);
	OptionsState(sf::RenderWindow& window, std::stack<State*>& states, sf::Sprite& bgsprite);
	~OptionsState();


	void update(const sf::Time& deltaTime) override final;
};