#pragma once
#include "Ammunition.h"
#include "Weapon.h"

class HasWeapons
{
private:
	//Some container for weapons
	// Maybe some internal counter, for weapons that autofire
	// some enum for differentiating weapons
	// maybe some bool if can shoot more than one weapon
public:
	HasWeapons();
	virtual ~HasWeapons();

	void addWeapon(Weapon* weapon);
	void shoot();
};