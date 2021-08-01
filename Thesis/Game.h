#pragma once

#include "State.h"


class Game
{
private:
	sf::RenderWindow m_Window;
	std::stack<State*> m_States;

	sf::Event sfevent;

	void initWindow();
	void initStates();
	
	void processEvents();
	void update(sf::Time deltaTime);
	void render();

public:
	Game(const Game&) = delete;
	Game& operator=(const Game&) = delete;

	Game();
	void run(int minFPS);
};

