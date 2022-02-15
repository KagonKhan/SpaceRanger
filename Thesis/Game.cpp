#include "pch.h"
#include "Game.h"
#include "MainMenuState.h"
#include "PlayerShip.h"

Game::Game()
{
	BOOST_LOG_TRIVIAL(info) << "Game ctor";
	Configuration::initialize();
	initWindow();
	initStates();
	initCursor();
}

void Game::initWindow()
{
	Helpers::CreateWindow(m_Window);

	m_GameView = m_Window.getDefaultView();
	//m_GameView.zoom(2.f);
	m_Window.setView(m_GameView);

}
void Game::initStates()
{
	m_States.emplace(new MainMenuState(m_Window, m_States));
}

void Game::initCursor()
{
	Animation::Line frames{ 40,10,6 };
	auto  *cursor_anim = new Animation(&Configuration::textures_game.get(Configuration::TexturesGameState::cursor));
	cursor_anim->addFrames(frames);
	
	m_Cursor.setAnimation(cursor_anim);
	m_Cursor.setFrameTime(sf::seconds(0.1f));
	m_Cursor.play();

}

void Game::processEvents()
{
	while (m_Window.pollEvent(sfevent))
	{
		if (sfevent.type == sf::Event::Closed)
			m_Window.close(); //close the window
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::C))
			system("CLS");
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Add)) {
			//m_GameSpeed += 0.05f;
			//if (m_GameSpeed >= 6.f) m_GameSpeed = 6.f;

		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Subtract)) {
			//m_GameSpeed -= 0.05f;
			//if (m_GameSpeed <= .1f) m_GameSpeed = .1f;

		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R)) {
			//m_GameView = m_Window.getDefaultView();
			//m_GameView.zoom(2.f);
			//m_Window.setView(m_GameView);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::P)) {
			return;
		}

		if (sfevent.type == sf::Event::MouseWheelMoved) {
			//auto view = m_Window.getView();

			//if (sfevent.mouseWheel.delta < 0)
			//	view.zoom(1.01f);
			//else if (sfevent.mouseWheel.delta > 0)
			//	view.zoom(0.99f);


			//m_Window.setView(view);
		}


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
	if (!m_States.empty()) {
		m_States.top()->update(deltaTime);

		if (m_States.top()->shouldQuit()) {
			m_States.pop();
			return;
		}

		if (m_States.top()->forcedQuit()) {
			while (!m_States.empty())
				m_States.pop();
			return;
		}
	}
}

void Game::render()
{
	m_Window.clear();
	if (!m_States.empty())
		m_Window.draw(*m_States.top());
	renderMouse();
	m_Window.display();
}

void Game::renderMouse()
{
	m_Window.draw(m_Cursor);
}

Game* Game::getInstance()
{
	static Game* INSTANCE = new Game;
	return INSTANCE;
}

void Game::run(int minFPS)
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate;
	sf::Time TimePerFrame = sf::seconds(1.f / minFPS);

	while (m_Window.isOpen()) {
		if (m_States.empty())
			m_Window.close();


		processEvents();
		timeSinceLastUpdate = clock.restart();

		// If the game runs slower than it should
		// Update if many times, before rendering
		while (timeSinceLastUpdate >= TimePerFrame) {
			timeSinceLastUpdate -= TimePerFrame;

			update(TimePerFrame * m_GameSpeed);
		}
		update(timeSinceLastUpdate * m_GameSpeed);
		render();
	}
}