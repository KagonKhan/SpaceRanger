#pragma once
#include "Ammunition.h"
#include "Weapon.h"

class HasWeapons
{
protected:
	std::vector<std::unique_ptr<Weapon>> m_Weapons;
	enum class WeaponType { Laser, Missile, Beam };

	void initWeapon(const sf::Vector2f& pos, const sf::Vector2f& offset, float firing_rate, WeaponType weapon_type, float rotation = 180.f, Entity::opt_ref parent = std::nullopt);

	//Some container for weapons
	// Maybe some internal counter, for weapons that autofire
	// some enum for differentiating weapons
	// maybe some bool if can shoot more than one weapon
public:
	HasWeapons();
	virtual ~HasWeapons();

	void addWeapon(std::unique_ptr<Weapon> weapon);

	void shoot();
};