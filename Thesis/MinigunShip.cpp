#include "pch.h"
#include "MinigunShip.h"

MinigunShip::MinigunShip()
	:MinigunShip(Configuration::TexturesShips::enemy_ship_minigun)
{
}

MinigunShip::MinigunShip(Configuration::TexturesShips tex_id)
	: EnemyShip(100.f, tex_id)
{
	initWeapons();
	m_Speed = 175.f;
}


void MinigunShip::initWeapons()
{
	addWeapon(m_Position, sf::Vector2f(-35.f / 2.f, 10.f),  5.f, WeaponType::Laser, 0.f);
	addWeapon(m_Position, sf::Vector2f( 35.f / 2.f, 10.f),  5.f, WeaponType::Laser, 0.f);
	addWeapon(m_Position, sf::Vector2f(-18.f / 2.f, 20.f),  5.f, WeaponType::Laser, 0.f);
	addWeapon(m_Position, sf::Vector2f( 18.f / 2.f, 20.f),  5.f, WeaponType::Laser, 0.f);

	for (auto&& weapon : m_Weapons)
		weapon->setVisible(false);
}

void MinigunShip::updateIndividualBehavior(const sf::Time& deltaTime)
{
	shoot(deltaTime);
}

void MinigunShip::shoot(const sf::Time&)
{

	HasWeapons::shoot();

}
