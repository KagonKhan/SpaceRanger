#pragma once
#include "World.h"
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
class Game
{
private:
	sf::RenderWindow m_Window;
	World m_World;

	void processEvents();
	void update(sf::Time deltaTime);
	void render();

public:
	Game(const Game&) = delete;
	Game& operator=(const Game&) = delete;

	Game(sf::VideoMode size, std::string title, int frameRateLimit, bool verticalSync);
};

