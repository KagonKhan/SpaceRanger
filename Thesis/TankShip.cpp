#include "pch.h"
#include "TankShip.h"

TankShip::TankShip(Configuration::TexturesShips tex_id)
	: EnemyShip(100.f, tex_id)
{
	initWeapons();
}

TankShip::~TankShip()
{
	// TODO this class will have unique weapon (shell weapon) large cannon, slow rate, giant blast
	// Probably have energy shield
}


void TankShip::initWeapons()
{
	initWeapon(m_Position, sf::Vector2f(-31.f, 0.f), 2.25f, WeaponType::Laser, 0.f);


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

void TankShip::onDestroy()
{
	Ship::onDestroy();
}

