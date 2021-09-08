#include "pch.h"
#include "Meteor.h"

void Meteor::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_Shape);
	target.draw(m_Sprite);
}


void Meteor::update(sf::Time deltaTime)
{
}
