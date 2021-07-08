#include "Meteor.h"

void Meteor::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_Shape);
	target.draw(m_Sprite);
}

int Meteor::getPoints() const
{
	return 100;
}

bool Meteor::isCollide(const Entity& other) const
{
	return false;
}

void Meteor::update(sf::Time deltaTime)
{
}
