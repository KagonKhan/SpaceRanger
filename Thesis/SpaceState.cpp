#include "pch.h"
#include "SpaceState.h"
#include "Player.h"
void SpaceState::initGUI()
{
}

void SpaceState::initPlayer()
{
	sf::Vector2f pos(m_Window.getSize());
	pos.y -= 300;
	pos.x /= 2.f;
	
	m_Player->setPosition(pos);
}

void SpaceState::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(*m_Player);
}


void SpaceState::processEvents(const sf::Event& sfevent)
{
}

SpaceState::SpaceState(sf::RenderWindow& window, std::stack<State*>& states)
	: State(window, states), ui(window),
	m_Player(Configuration::player = new Player(Configuration::Textures::PlayerAvatar0, sf::Vector2f(m_Window.getSize())))
{
	initPlayer();
}

SpaceState::~SpaceState()
{
}

void SpaceState::update(const sf::Time& deltaTime)
{
	m_Player->update(deltaTime);
}
