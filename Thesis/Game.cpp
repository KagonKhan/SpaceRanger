#include "Game.h"

Game::Game(sf::VideoMode size, std::string title, int frameRateLimit, bool verticalSync)
	: m_Window(size,title), m_World(size.width, size.height)
{
	m_Window.setFramerateLimit(frameRateLimit);
	m_Window.setVerticalSyncEnabled(verticalSync);
	m_Window.setMouseCursorGrabbed(true);
	
	/* Custom Cursor*/
}
