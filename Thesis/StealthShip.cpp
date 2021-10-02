#include "pch.h"
#include "StealthShip.h"

StealthShip::StealthShip()
	: StealthShip(Configuration::TexturesShips::enemy_ship_stealth)
{
}

StealthShip::StealthShip(Configuration::TexturesShips tex_id)
	: EnemyShip(100.f, tex_id)
{
	initWeapons();
	m_Sprite.setScale(0.5f, 0.5f);
	m_Speed = 2000.f;
}


void StealthShip::initWeapons()
{
	addWeapon(m_Position, sf::Vector2f(-53.f, 0.f), 0.5f, WeaponType::Laser, 0.f);
	addWeapon(m_Position, sf::Vector2f( 53.f, 0.f), 0.5f, WeaponType::Laser, 0.f);

	addWeapon(m_Position, sf::Vector2f(-48.f, 0.f), 0.5f, WeaponType::Laser, 0.f);
	addWeapon(m_Position, sf::Vector2f( 48.f, 0.f), 0.5f, WeaponType::Laser, 0.f);

	addWeapon(m_Position, sf::Vector2f(-38.f, 0.f), 0.5f, WeaponType::Laser, 0.f);
	addWeapon(m_Position, sf::Vector2f( 38.f, 0.f), 0.5f, WeaponType::Laser, 0.f);

	addWeapon(m_Position, sf::Vector2f(-27.f, 0.f), 0.5f, WeaponType::Laser, 0.f);
	addWeapon(m_Position, sf::Vector2f( 27.f, 0.f), 0.5f, WeaponType::Laser, 0.f);


	for (auto&& weapon : m_Weapons)
		weapon->setVisible(false);
}

void StealthShip::updateIndividualBehavior(const sf::Time& deltaTime)
{
	shoot(deltaTime);
}

void StealthShip::shoot(const sf::Time& deltaTime)
{

	HasWeapons::shoot();
	
}
