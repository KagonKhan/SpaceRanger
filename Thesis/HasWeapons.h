#pragma once
#include "Ammunition.h"
#include "Weapon.h"

class HasWeapons
{
private:
	bool makeAnotherSound(std::vector<Weapon::ptr>::iterator weaponIt);

protected:
	enum class	WeaponType		{ Laser, Missile, Beam };
	std::vector<Weapon::ptr>	m_Weapons;

	Weapon::ptr& addWeapon(const sf::Vector2f& pos, const sf::Vector2f& offset, float firing_rate, WeaponType weapon_type, float rotation = 180.f, Entity::opt_ref parent = std::nullopt);

public:
	virtual ~HasWeapons() = default;


	void shoot();
};