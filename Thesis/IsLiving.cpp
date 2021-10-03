#include "pch.h"
#include "IsLiving.h"


IsLiving::IsLiving(float max_hp, int armor, int plating)
	: m_ShipStats({max_hp, max_hp, armor, plating, true})
{
}

void IsLiving::receiveDamage(float amount) 
{
	m_ShipStats.m_CurrentHp -= amount;
}

