#include "pch.h"

#include "HasWeapons.h"


HasWeapons::HasWeapons()
{
}

HasWeapons::~HasWeapons()
{
}

void HasWeapons::addWeapon(Weapon* weapon)
{
	m_Weapons.push_back(weapon);
}

//possibly add some index 
void HasWeapons::shoot()
{
	for (Weapon* weapon : m_Weapons)
		weapon->shoot();
}
