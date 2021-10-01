#include "pch.h"
#include "ScoutShipV2.h"

ScoutShipV2::ScoutShipV2()
	:ScoutShipV2(Configuration::TexturesShips::enemy_ship_scout_v2)
{
}

ScoutShipV2::ScoutShipV2(Configuration::TexturesShips tex_id)
	: EnemyShip(100.f, tex_id)
{
	initWeapons();
}

ScoutShipV2::~ScoutShipV2()
{
}


void ScoutShipV2::initWeapons()
{
	initWeapon(m_Position, sf::Vector2f(-70.f, 0.f), 0.5f, WeaponType::Laser, 0.f);
	initWeapon(m_Position, sf::Vector2f(70.f, 0.f), 0.5f, WeaponType::Laser, 0.f);

	for (auto&& weapon : m_Weapons)
		weapon->setVisible(false);
}

void ScoutShipV2::updateIndividualBehavior(const sf::Time& deltaTime)
{
	shoot(deltaTime);
}

void ScoutShipV2::shoot(const sf::Time& deltaTime)
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

void ScoutShipV2::onDestroy()
{
	Ship::onDestroy();
}

