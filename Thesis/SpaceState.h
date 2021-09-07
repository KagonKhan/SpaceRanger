#pragma once
#include "State.h"

class SpaceState : public State
{
private:
	UserInterface m_UI;
	PlayerShip& m_Player;
	void initGUI();
	void initPlayer();


	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override final;


public:
	SpaceState(sf::RenderWindow& window, std::stack<State::ptr>& states, PlayerShip& player);
	virtual ~SpaceState();



	void processEvents(const sf::Event& sfevent);
	void update(const sf::Time& deltaTime)  override final;
};

