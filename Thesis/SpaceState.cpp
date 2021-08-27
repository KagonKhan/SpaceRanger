#include "pch.h"
#include "SpaceState.h"
#include "PlayerShip.h"

void SpaceState::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_Player);
}

SpaceState::SpaceState(sf::RenderWindow& window, std::stack<State*>& states, PlayerShip& player)
	: State(window, states), ui(window),
	m_Player(player)
{
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
}

SpaceState::~SpaceState()
{
}

void SpaceState::update(const sf::Time& deltaTime)
{
	m_Player.update(deltaTime);
}
