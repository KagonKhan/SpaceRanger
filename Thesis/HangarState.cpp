#include "pch.h"
#include "HangarState.h"

void HangarState::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (!m_Creation.getIsDone())
		target.draw(m_Creation);

	target.draw(m_Background);
}

HangarState::HangarState(sf::RenderWindow& window, std::stack<State*>& states)
	: State(window, states), m_Creation(), m_Background(Configuration::textures.get(Configuration::Textures::Hangar))
{
}

void HangarState::processEvents(const sf::Event& sfevent)
{
}

void HangarState::update(const sf::Time& deltaTime)
{
}
