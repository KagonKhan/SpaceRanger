#include "pch.h"
#include "RocketShip.h"

RocketShip::RocketShip()
	: RocketShip(Configuration::TexturesShips::enemy_ship_rocket)
{
}

RocketShip::RocketShip(Configuration::TexturesShips tex_id)
	: EnemyShip(100.f, tex_id)
{
	initWeapons();
}

RocketShip::~RocketShip()
{
}


void RocketShip::initWeapons()
{
	initWeapon(m_Position, sf::Vector2f(-30.f, -20.f), 0.5f, WeaponType::Missile, 0.f);
	initWeapon(m_Position, sf::Vector2f( 30.f, -20.f), 0.5f, WeaponType::Missile, 0.f);

	for (auto&& weapon : m_Weapons)
		weapon->setVisible(false);
}

void RocketShip::updateIndividualBehavior(const sf::Time& deltaTime)
{
	shoot(deltaTime);
}

void RocketShip::shoot(const sf::Time& deltaTime)
{

	HasWeapons::shoot();

}

void RocketShip::onDestroy()
{
	Ship::onDestroy();
}

