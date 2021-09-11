#include "pch.h"
#include "BeamShip.h"

BeamShip::BeamShip(Configuration::TexturesShips tex_id)
	: EnemyShip(100.f, tex_id)
{
	initWeapons();
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
}

