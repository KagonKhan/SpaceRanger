#include "pch.h"
#include "Game.h"
#include "MainMenuState.h"

Game::Game()
	: m_Window()
{
	Configuration::initialize();
	initWindow();
	/* Custom Cursor*/


	initStates();
}

void Game::initWindow()
{
	std::ifstream settings("../media/config/screen.txt");
	
	std::string title;
	std::getline(settings, title);
	
	int x, y;
	settings >> x >> y;

	int framerate;
	settings >> framerate;
	
	bool fullscreen;
	settings >> fullscreen;
		
	bool borderless;
	settings >> borderless;

	bool vsync;
	settings >> vsync;

	using namespace sf::Style;

	if (fullscreen) {
		if (borderless)
			m_Window.create(sf::VideoMode::getDesktopMode(), title, None);
		else
			m_Window.create(sf::VideoMode::getDesktopMode(), title, Titlebar | Close | Fullscreen);
	}
	else
		m_Window.create(sf::VideoMode(x, y), title, Titlebar | Close );


	m_Window.setFramerateLimit(framerate);
	m_Window.setVerticalSyncEnabled(vsync);
}

/* TODO: check if this doesn't cause any WHACKY behavior*/
void Game::initStates()
{
	m_States.emplace(std::move(new MainMenuState(m_Window, m_States)));
}

void Game::processEvents()
{
	while (m_Window.pollEvent(sfevent))
	{
		if (sfevent.type == sf::Event::Closed)
			m_Window.close(); //close the window

		m_States.top()->processEvents(sfevent);
	}

}

/* TODO: maybe add safeguards for empty containers, altho does it matter? */
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
		// Update if many times, before rendering
		while (timeSinceLastUpdate > TimePerFrame) {
			timeSinceLastUpdate -= TimePerFrame;

			update(TimePerFrame);
		}
		update(timeSinceLastUpdate);
		render();
	}
}
