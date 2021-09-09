#include "pch.h"
#include "HasWeapons.h"
#include "Weaponry.h"

HasWeapons::HasWeapons() {}
HasWeapons::~HasWeapons(){}

void HasWeapons::initWeapon(const sf::Vector2f& pos, const sf::Vector2f& offset, float firing_rate, WeaponType weapon_type, float rotation, Entity::opt_ref parent)
{
	switch (weapon_type) {
	case WeaponType::Laser: {
		std::unique_ptr<LaserTurret> weapon(new LaserTurret(Configuration::TexturesWeaponry::turret_laser));
		addWeapon(std::move(weapon));

		break;
	}
	case WeaponType::Missile: {
		std::unique_ptr<MissileTurret> weapon(new MissileTurret(Configuration::TexturesWeaponry::turret_laser));
		addWeapon(std::move(weapon));

		break;
	}
	case WeaponType::Beam: {
		std::unique_ptr<BeamTurret> weapon(new BeamTurret(Configuration::TexturesWeaponry::turret_laser, parent));
		addWeapon(std::move(weapon));

		break;
	}
	}

	m_Weapons.back()->setPosition(pos);
	m_Weapons.back()->setIsWeaponActive(true);
	m_Weapons.back()->setWeaponOffset(offset);
	m_Weapons.back()->setFiringRate(firing_rate);
	m_Weapons.back()->setSpriteRotation(rotation);
	m_Weapons.back()->setIsWeaponActive(true);
}

void HasWeapons::addWeapon(std::unique_ptr<Weapon> weapon)
{
	m_Weapons.push_back(std::move(weapon));
}

//possibly add some index 
void HasWeapons::shoot()
{
	for (auto&& weapon : m_Weapons) {
		if(weapon->isActive())
			weapon->shoot();
	
	}
}
