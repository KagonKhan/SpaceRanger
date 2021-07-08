#pragma once
#include "Enemy.h"
class Meteor : public Enemy
{
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:
	Meteor(const Meteor&) = delete;
	Meteor operator=(const Meteor&) = delete;

	using Enemy::Enemy;

	virtual int getPoints() const;
	
	
	virtual bool isCollide(const Entity& other) const;
	virtual void update(sf::Time deltaTime);
};

