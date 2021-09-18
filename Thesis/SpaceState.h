#pragma once
#include "State.h"
#include "PlayerShip.h"
#include <stack>
#include "SpaceBackground.h"
#include "Level.h"
#include "Level_One.h"

class SpaceState : 
	public State
{
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override final;
	
	UserInterface m_UI;
	//PlayerShip& m_Player;
	PlayerShip m_Player;
	SpaceBackground m_Background;
	Level m_Level;
	std::unique_ptr<LevelManager> m_LevelManager;


	void initGUI();
	void initPlayer();


public:
	//SpaceState(sf::RenderWindow& window, std::stack<State::ptr>& states, PlayerShip& player);
	SpaceState(sf::RenderWindow& window, std::stack<State::ptr>& states);
	virtual ~SpaceState();



	void processEvents(const sf::Event& sfevent);
	void update(const sf::Time& deltaTime)  override final;
};

