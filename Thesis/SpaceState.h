#pragma once
#include "State.h"

class SpaceState : public State
{
	UI ui;
	void initGUI();

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override final;

	void Options();
	void NewGame();
public:

	void processEvents(const sf::Event& sfevent);
	SpaceState(sf::RenderWindow& window, std::stack<State*>& states);
	~SpaceState();


	void update(const sf::Time& deltaTime)  override final;
};

