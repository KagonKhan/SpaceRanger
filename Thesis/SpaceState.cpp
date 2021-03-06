#include "pch.h"
#include "SpaceState.h"
#include "PlayerShip.h"
#include "EndState.h"
#include "StealthShip.h"


void SpaceState::draw(sf::RenderTarget& target, sf::RenderStates) const
{
	target.draw(m_Background);
	target.draw(m_Player);
	target.draw(m_Level);

	target.draw(bounding);
}

SpaceState::SpaceState(sf::RenderWindow& window, std::stack<State::ptr>& states)
	: State(window, states), m_Player((Configuration::TexturesShips)0, (sf::Vector2f)m_Window.getSize()),
	m_Background(window, 1, 2), m_Level(m_Window, m_Player)
{
	BOOST_LOG_TRIVIAL(info) << "SpaceState ctor";

	initPlayer();

	m_LevelManager = std::make_unique<LevelManagerOne>(m_Level);

	bounding.setSize((sf::Vector2f)window.getSize());
	bounding.setOutlineColor(sf::Color::White);
	bounding.setOutlineThickness(5.f);
	bounding.setFillColor(sf::Color::Transparent);
}


void SpaceState::initGUI()
{

}
 
void SpaceState::initPlayer()
{
	sf::Vector2f pos(m_Window.getSize());
	pos.y -= 300;
	pos.x /= 2.f;
	
	m_Player.setPosition(pos);


	Configuration::player = &m_Player;
}


void SpaceState::processEvents(const sf::Event& sfevent)
{
	if (sfevent.type == sf::Event::KeyPressed && sfevent.key.code == sf::Keyboard::Key::Escape)
		m_ShouldQuit = true;
}

SpaceState::~SpaceState()
{
	BOOST_LOG_TRIVIAL(info) << "SpaceState dtor";

	Configuration::player = nullptr;
}

void SpaceState::update(const sf::Time& deltaTime)
{
	if (m_ShouldQuit) {
		m_States.pop();
		return;
	}
	if (m_LevelManager->isFinished())
		m_States.emplace(new EndState(m_Window, m_States));


	if (m_Player.getHP() <= 0.0)
		m_ShouldQuit = true;


	m_Player.update(deltaTime);
	m_Background.update(deltaTime);
	m_LevelManager->update(deltaTime);
}


