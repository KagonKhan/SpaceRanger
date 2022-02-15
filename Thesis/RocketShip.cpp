#include "pch.h"
#include "RocketShip.h"
#include "PlayerShip.h"


RocketShip::RocketShip()
	: RocketShip(Configuration::TexturesShips::enemy_ship_rocket)
{
}

RocketShip::RocketShip(Configuration::TexturesShips tex_id)
	: EnemyShip(100.f, tex_id)
{
	initWeapons();
	m_Speed = 100.f;
}


void RocketShip::initWeapons()
{
	addWeapon(m_Position, sf::Vector2f(-30.f / 2.f, -20.f), 0.5f, WeaponType::Missile, 0.f)->setTarget(Configuration::player);
	addWeapon(m_Position, sf::Vector2f( 30.f / 2.f, -20.f), 0.5f, WeaponType::Missile, 0.f)->setTarget(Configuration::player);

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
