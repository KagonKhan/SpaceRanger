#pragma once
#include "Entity.h"
class Meteor :
	public Entity
{
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:


	virtual void update(sf::Time deltaTime);
};

