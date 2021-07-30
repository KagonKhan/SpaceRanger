#include "pch.h"
#include "SpaceState.h"

void SpaceState::initGUI()
{
}

void SpaceState::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
}

void SpaceState::Options()
{
}

void SpaceState::NewGame()
{
}

void SpaceState::processEvents(const sf::Event& sfevent)
{
}

SpaceState::SpaceState(sf::RenderWindow& window, std::stack<State*>& states)
	: State(window, states), ui(window)
{
}

SpaceState::~SpaceState()
{
}

void SpaceState::update(const sf::Time& deltaTime)
{
}
