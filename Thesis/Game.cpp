#include "pch.h"
#include "Game.h"
#include "MainMenuState.h"

Game::Game(sf::VideoMode size, std::string title, int frameRateLimit, bool verticalSync)
	: m_Window(size,title)
{
	initWindow(frameRateLimit, verticalSync);
	
	/* Custom Cursor*/


	initStates();
}

void Game::initWindow(int frameRateLimit, bool verticalSync)
{
	m_Window.setFramerateLimit(frameRateLimit);
	m_Window.setVerticalSyncEnabled(verticalSync);
	m_Window.setMouseCursorGrabbed(false);
}


void Game::initStates()
{
	m_States.emplace(std::move(new MainMenuState(m_Window, m_States)));
}

void Game::processEvents()
{
	while (m_Window.pollEvent(sfevent))
	{
		if ((sfevent.type == sf::Event::Closed) or (sfevent.type == sf::Event::KeyPressed and sfevent.key.code == sf::Keyboard::Escape))
			m_Window.close(); //close the window

		m_States.top()->processEvents(sfevent);
	}

}

void Game::update(sf::Time deltaTime)
{
	m_States.top()->update(deltaTime);
}

void Game::render()
{
	m_Window.clear();
	m_Window.draw(*m_States.top());
	m_Window.display();
}

void Game::run(int minFPS)
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate;
	sf::Time TimePerFrame = sf::seconds(1.f / minFPS);

	while (m_Window.isOpen()) {
		processEvents();
		timeSinceLastUpdate = clock.restart();

		// If the game runs slower than it should
		while (timeSinceLastUpdate > TimePerFrame) {
			timeSinceLastUpdate -= TimePerFrame;

			update(TimePerFrame);
		}
		update(timeSinceLastUpdate);
		render();
	}
}
