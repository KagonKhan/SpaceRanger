#pragma once
#include "State.h"

class SpaceState : public State
{
private:
	UI ui;
	Player* m_Player;
	void initGUI();
	void initPlayer();


	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override final;


public:

	void processEvents(const sf::Event& sfevent);
	SpaceState(sf::RenderWindow& window, std::stack<State*>& states);
	~SpaceState();


	void update(const sf::Time& deltaTime)  override final;
};

