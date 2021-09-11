#include "pch.h"
#include "StealthShip.h"

StealthShip::StealthShip(Configuration::TexturesShips tex_id)
	: EnemyShip(100.f, tex_id)
{
	initWeapons();
}

StealthShip::~StealthShip()
{
	// TODO implement invisibility
}


void StealthShip::initWeapons()
{
	initWeapon(m_Position, sf::Vector2f(-53.f, 0.f), 0.5f, WeaponType::Laser, 0.f);
	initWeapon(m_Position, sf::Vector2f( 53.f, 0.f), 0.5f, WeaponType::Laser, 0.f);

	initWeapon(m_Position, sf::Vector2f(-48.f, 0.f), 0.5f, WeaponType::Laser, 0.f);
	initWeapon(m_Position, sf::Vector2f( 48.f, 0.f), 0.5f, WeaponType::Laser, 0.f);

	initWeapon(m_Position, sf::Vector2f(-38.f, 0.f), 0.5f, WeaponType::Laser, 0.f);
	initWeapon(m_Position, sf::Vector2f( 38.f, 0.f), 0.5f, WeaponType::Laser, 0.f);

	initWeapon(m_Position, sf::Vector2f(-27.f, 0.f), 0.5f, WeaponType::Laser, 0.f);
	initWeapon(m_Position, sf::Vector2f( 27.f, 0.f), 0.5f, WeaponType::Laser, 0.f);


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

void StealthShip::onDestroy()
{
}
