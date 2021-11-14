#include "pch.h"
#include "TankShip.h"

TankShip::TankShip()
	:TankShip(Configuration::TexturesShips::enemy_ship_tank)
{
}

TankShip::TankShip(Configuration::TexturesShips tex_id)
	: EnemyShip(100.f, tex_id)
{
	initWeapons();
	m_Speed = 50.f;
}


void TankShip::initWeapons()
{
	addWeapon(m_Position, sf::Vector2f(-31.f /2.f, 0.f), 2.25f, WeaponType::Laser, 0.f);


	for (auto&& weapon : m_Weapons)
		weapon->setVisible(false);
}

void TankShip::updateIndividualBehavior(const sf::Time& deltaTime)
{
	shoot(deltaTime);
}

void TankShip::shoot(const sf::Time& deltaTime)
{

	HasWeapons::shoot();

}


