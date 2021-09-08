#include "pch.h"
#include "ScoutEnemyShip.h"



ScoutEnemyShip::ScoutEnemyShip(Configuration::TexturesShips tex_id)
	: EnemyShip(100.f, tex_id) 
{
	initWeapons();
	srand(reinterpret_cast<unsigned int>(this));
}

ScoutEnemyShip::~ScoutEnemyShip()
{
}


void ScoutEnemyShip::initWeapons()
{
	initWeapon(sf::Vector2f(-70.f, 0.f), 0.5f, WeaponType::Laser, 0.f);
	initWeapon(sf::Vector2f( 70.f, 0.f), 0.5f, WeaponType::Laser, 0.f);

	for (auto&& weapon : m_Weapons)
		weapon->setVisible(false);
}

void ScoutEnemyShip::update(const sf::Time& deltaTime)
{
	static float time = 0.f;
	static float max = 5 + rand() % 10;
	time += deltaTime.asSeconds();

	if (time >= max) {
		time = 0.f;
		max = 5 + rand() % 10;
		
		shoot();
	}
	for (auto&& weapon : m_Weapons)
		weapon->update(deltaTime);
}

