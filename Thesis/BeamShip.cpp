#include "pch.h"
#include "BeamShip.h"
#include "BeamTurret.h"

BeamShip::BeamShip()
	: BeamShip(Configuration::TexturesShips::enemy_ship_beam)
{
}

BeamShip::BeamShip(Configuration::TexturesShips tex_id)
	: EnemyShip(100.f, tex_id)
{
	initWeapons();
	m_Speed = 50.f;
}

BeamShip::~BeamShip()
{
}


void BeamShip::initWeapons()
{
	initWeapon(m_Position, sf::Vector2f(5.f, 20.f), 0.2f, WeaponType::Beam, 0.f);

	for (auto&& weapon : m_Weapons)
		weapon->setVisible(false);
}

void BeamShip::updateIndividualBehavior(const sf::Time& deltaTime)
{
	shoot(deltaTime);
}

void BeamShip::shoot(const sf::Time& deltaTime)
{

	HasWeapons::shoot();
	
}

void BeamShip::onDestroy()
{
	Ship::onDestroy();
	dynamic_cast<BeamTurret*>(m_Weapons.back().get())->stop();
}

