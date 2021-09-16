#include "pch.h"
#include "MinigunShip.h"

MinigunShip::MinigunShip(Configuration::TexturesShips tex_id)
	: EnemyShip(100.f, tex_id)
{
	initWeapons();
	puts("MinigunShip\tctor");
}

MinigunShip::~MinigunShip()
{
}


void MinigunShip::initWeapons()
{
	initWeapon(m_Position, sf::Vector2f(-35.f, 10.f),  5.f, WeaponType::Laser, 0.f);
	initWeapon(m_Position, sf::Vector2f( 35.f, 10.f),  5.f, WeaponType::Laser, 0.f);
	initWeapon(m_Position, sf::Vector2f(-18.f, 20.f),  5.f, WeaponType::Laser, 0.f);
	initWeapon(m_Position, sf::Vector2f( 18.f, 20.f),  5.f, WeaponType::Laser, 0.f);

	for (auto&& weapon : m_Weapons)
		weapon->setVisible(false);
}

void MinigunShip::updateIndividualBehavior(const sf::Time& deltaTime)
{
	shoot(deltaTime);
}

void MinigunShip::shoot(const sf::Time& deltaTime)
{

	HasWeapons::shoot();

}

void MinigunShip::onDestroy()
{
	Ship::onDestroy();
}

