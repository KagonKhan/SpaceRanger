#include "pch.h"
#include "HasWeapons.h"
#include "Weaponry.h"


void HasWeapons::initWeapon(const sf::Vector2f& pos, const sf::Vector2f& offset, float firing_rate, WeaponType weapon_type, float rotation, Entity::opt_ref parent)
{
	Weapon::ptr weapon;

	switch (weapon_type) {
	case WeaponType::Laser: 
		weapon = std::make_unique<LaserTurret>();			break;
	case WeaponType::Missile: 
		weapon = std::make_unique<MissileTurret>(Configuration::TexturesWeaponry::turret_laser);		break;
	case WeaponType::Beam:
		weapon = std::make_unique<BeamTurret>(Configuration::TexturesWeaponry::turret_laser, parent);	break;
	default:																							break;
	}
	
		addWeapon(std::move(weapon));
	m_Weapons.back()->setPosition(pos);
	m_Weapons.back()->setIsWeaponActive(true);
	m_Weapons.back()->setOffset(offset);
	m_Weapons.back()->setFiringRate(firing_rate);
	m_Weapons.back()->setSpriteRotation(rotation);
	m_Weapons.back()->setIsWeaponActive(true);
}



void HasWeapons::shoot()
{
	bool makeSound{ true };

	for (auto&& it = begin(m_Weapons); it != end(m_Weapons); ++it)	
		if (auto&& weapon = *it; weapon->isActive()) {
			weapon->shoot(makeSound);
			makeSound = makeAnotherSound(it);
		}
}

// For this function to work as it's supposed to, the weapon container would have to be grouped by weapon type!
// TODO: measure how complex this function is (time)
bool HasWeapons::makeAnotherSound(std::vector<Weapon::ptr>::iterator weaponIt)
{
	if (std::next(weaponIt) != end(m_Weapons)) {
		auto&& currWeapon = *weaponIt->get();
		auto&& nextWeapon = *std::next(weaponIt)->get();

		if (typeid(currWeapon).name() != typeid(nextWeapon).name())
			return true;
	}
	return false;
}
