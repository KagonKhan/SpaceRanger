#include "pch.h"
#include "BossEnemyShip.h"

BossEnemyShip::BossEnemyShip()
	: BossEnemyShip(Configuration::TexturesShips::enemy_ship_boss)
{
}

BossEnemyShip::BossEnemyShip(Configuration::TexturesShips tex_id)
	: EnemyShip(100.f, tex_id)
{
	initWeapons();
}

BossEnemyShip::~BossEnemyShip()
{
}


void BossEnemyShip::initWeapons()
{
	initWeapon(m_Position, sf::Vector2f(-70.f, 0.f), 0.5f, WeaponType::Laser, 0.f);
	initWeapon(m_Position, sf::Vector2f(70.f, 0.f), 0.5f, WeaponType::Laser, 0.f);

	for (auto&& weapon : m_Weapons)
		weapon->setVisible(false);
}

void BossEnemyShip::updateIndividualBehavior(const sf::Time& deltaTime)
{
	shoot(deltaTime);
}

void BossEnemyShip::shoot(const sf::Time& deltaTime)
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

void BossEnemyShip::onDestroy()
{
	Ship::onDestroy();
}

