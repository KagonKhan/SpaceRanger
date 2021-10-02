#include "pch.h"
#include "ScoutEnemyShip.h"

ScoutEnemyShip::ScoutEnemyShip()
	: ScoutEnemyShip(Configuration::TexturesShips::enemy_ship_scout)
{
}

ScoutEnemyShip::ScoutEnemyShip(Configuration::TexturesShips tex_id)
	: EnemyShip(100.f, tex_id) 
{
	initWeapons();
	m_Speed = 150.f;
}

ScoutEnemyShip::~ScoutEnemyShip()
{
}


void ScoutEnemyShip::initWeapons()
{
	initWeapon(m_Position, sf::Vector2f(-70.f, 0.f), 0.5f, WeaponType::Laser, 0.f);
	initWeapon(m_Position, sf::Vector2f( 70.f, 0.f), 0.5f, WeaponType::Laser, 0.f);

	for (auto&& weapon : m_Weapons)
		weapon->setVisible(false);
}

void ScoutEnemyShip::updateIndividualBehavior(const sf::Time& deltaTime)
{
	shoot(deltaTime);
}

void ScoutEnemyShip::shoot(const sf::Time& deltaTime)
{
	static float time = 0.f;
	static float max = 5 + rand() % 10;
	time += deltaTime.asSeconds();

	if (time >= max) {
		time = 0.f;
		max = 5 + rand() % 10;

		HasWeapons::shoot();
	}
}

void ScoutEnemyShip::onDestroy()
{
	Ship::onDestroy();
}

