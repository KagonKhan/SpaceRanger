#include "pch.h"
#include "Game.h"
#include "MainMenuState.h"

Game::Game()
	: m_Window()
{
	Configuration::initialize();
	initWindow();
	initStates();
	initCursor();
}

void Game::initWindow()
{
	Configuration::CreateWindow(m_Window);
}

void Game::initStates()
{
	m_States.emplace(std::move(new MainMenuState(m_Window, m_States)));
}

void Game::initCursor()
{
	Animation *cursor_anim = new Animation(&Configuration::textures.get(Configuration::Textures::Cursor));
	cursor_anim->addFramesLine(40, 10, 6);
	
	m_Cursor.setAnimation(cursor_anim);
	m_Cursor.setFrameTime(sf::seconds(0.1));
	m_Cursor.play();

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
void Game::update(const sf::Time& deltaTime)
{
	updateMouse(deltaTime);
	updateStates(deltaTime);
}

void Game::updateMouse(const sf::Time& deltaTime)
{
	m_Cursor.setPosition(static_cast<sf::Vector2f>(sf::Mouse::getPosition(m_Window)) - sf::Vector2f(8, 8.5));
	m_Cursor.update(deltaTime);
}

void Game::updateStates(const sf::Time& deltaTime)
{
	m_States.top()->update(deltaTime);
}

void Game::render()
{
	m_Window.clear();
	m_Window.draw(*m_States.top());
	renderMouse();
	m_Window.display();
}

void Game::renderMouse()
{
	m_Window.draw(m_Cursor);
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
