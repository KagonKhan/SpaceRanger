#include "pch.h"
#include "SpaceState.h"
#include "PlayerShip.h"

void SpaceState::draw(sf::RenderTarget& target, sf::RenderStates states) const
{

	target.draw(m_Background);
	target.draw(m_Player);
	target.draw(m_Level);
}

//SpaceState::SpaceState(sf::RenderWindow& window, std::stack<State::ptr>& states, PlayerShip& player)
//	: State(window, states)//,	m_Player(player)
//{
//	puts("SpaceState\tctor");
//	initPlayer();
//}
SpaceState::SpaceState(sf::RenderWindow& window, std::stack<State::ptr>& states)
	: State(window, states), m_Player((Configuration::TexturesShips)0, (sf::Vector2f)m_Window.getSize()),
	m_Background(window, 1, 2), m_Level(m_Window, m_Player)
{
	puts("SpaceState\tctor");

	

	initPlayer();
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
}


void SpaceState::processEvents(const sf::Event& sfevent)
{
	if (sfevent.type == sf::Event::KeyPressed)
		if (sfevent.key.code == sf::Keyboard::Key::Escape)
			m_ShouldQuit = true;
}

SpaceState::~SpaceState()
{
	puts("SpaceState\tdtor");
}

void SpaceState::update(const sf::Time& deltaTime)
{
	if (m_ShouldQuit) {
		m_States.pop();
		return;
	}
	m_Player.update(deltaTime);

	m_Background.update(deltaTime);
	m_Level.update(deltaTime);
}


