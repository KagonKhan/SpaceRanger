#pragma once
#include "Ammunition.h"
#include "Weapon.h"

class HasWeapons
{
protected:
	std::vector<std::unique_ptr<Weapon>> m_Weapons;

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