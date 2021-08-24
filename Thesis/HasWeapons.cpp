#include "pch.h"

#include "HasWeapons.h"


HasWeapons::HasWeapons()
{
}

HasWeapons::~HasWeapons()
{
}

void HasWeapons::addWeapon(std::unique_ptr<Weapon> weapon)
{
	m_Weapons.push_back(std::move(weapon));
}

//possibly add some index 
void HasWeapons::shoot()
{
	for (auto&& weapon : m_Weapons)
		weapon->shoot();
}
