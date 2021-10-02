#include "pch.h"
#include "SupportShip.h"

SupportShip::SupportShip()
	:SupportShip(Configuration::TexturesShips::enemy_ship_support)
{
}

SupportShip::SupportShip(Configuration::TexturesShips tex_id)
	: EnemyShip(100.f, tex_id)
{
	initWeapons();
	m_Speed = 100.f;
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
