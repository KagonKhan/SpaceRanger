#pragma once
#include "State.h"
#include "AnimatedSprite.h"
class Game
{
private:
	Game();
	Game(const Game&) = delete;
	Game& operator=(const Game&) = delete;
	Game(Game&&) = delete;
	Game& operator=(Game&&) = delete;


	sf::RenderWindow m_Window;
	sf::View m_GameView;

	std::stack<State::ptr> m_States;
	sf::Event sfevent;

	float m_GameSpeed{ 1.f };

	AnimatedSprite m_Cursor;

	void initWindow();
	void initStates();
	void initCursor();
	
	void processEvents();

	void update(const sf::Time& deltaTime);
	void updateMouse(const sf::Time& deltaTime);
	void updateStates(const sf::Time& deltaTime);

	void render();
	void renderMouse();

public:
	static Game* getInstance();

	void run(int minFPS);
};

