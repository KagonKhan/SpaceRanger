#include "pch.h"
#include "SupportShip.h"

SupportShip::SupportShip(Configuration::TexturesShips tex_id)
	: EnemyShip(100.f, tex_id)
{
	initWeapons();
}

SupportShip::~SupportShip()
{
	// TODO - add some forms of shields, maybe increases defense for nearby enemies,
	// generally either doesnt shoot or really weak
}


void SupportShip::initWeapons()
{

}

void SupportShip::updateIndividualBehavior(const sf::Time& deltaTime)
{
	shoot(deltaTime);
}

void SupportShip::shoot(const sf::Time& deltaTime)
{

}

void SupportShip::onDestroy()
{
}

