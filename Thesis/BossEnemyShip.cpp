#include "pch.h"
#include "BossEnemyShip.h"
#include "PlayerShip.h"


BossEnemyShip::BossEnemyShip()
	: BossEnemyShip(Configuration::TexturesShips::enemy_ship_boss)
{
}

BossEnemyShip::BossEnemyShip(Configuration::TexturesShips tex_id)
	: EnemyShip(100.f, tex_id)
{
	initWeapons();

	m_Speed = 25.f;
}



void BossEnemyShip::initWeapons()
{
	addWeapon(m_Position, sf::Vector2f(-70.f / 2.f, 0.f), 0.5f, WeaponType::Laser, 0.f);
	addWeapon(m_Position, sf::Vector2f( 70.f / 2.f, 0.f), 0.5f, WeaponType::Laser, 0.f);

	for (auto&& weapon : m_Weapons)
		weapon->setVisible(true);
}

void BossEnemyShip::updateIndividualBehavior(const sf::Time& deltaTime)
{
	shoot(deltaTime);
}

void BossEnemyShip::shoot(const sf::Time& deltaTime)
{
	float time = 0.f;

	float max = Helpers::getRandom(5.f, 15.f);
	time += deltaTime.asSeconds();

	if (time >= max) {
		time = 0.f;
		max = Helpers::getRandom(5.f, 15.f);

		HasWeapons::shoot();
	}
}
