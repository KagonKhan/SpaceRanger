#include "pch.h"
#include "IsLiving.h"


IsLiving::ShipStats& IsLiving::getShipStats()
{
	return m_ShipStats;
}

IsLiving::IsLiving(double max_hp, int armor, int plating)
	: m_ShipStats({max_hp, max_hp, armor, plating, true})
{
}

IsLiving::~IsLiving()
{
	m_ShipStats.m_IsAlive = false;
}

void IsLiving::receiveDamage(double amount)
{
	m_ShipStats.m_CurrentHp -= amount;
	if (m_ShipStats.m_CurrentHp <= 0)
		m_ShipStats.m_IsAlive = false;
}

bool IsLiving::isAlive() const
{
	return m_ShipStats.m_IsAlive;
}

double IsLiving::getCurrentHP() const
{
	return m_ShipStats.m_CurrentHp;
}

int IsLiving::getCurrentPlating() const
{
	return m_ShipStats.m_Plating;
}

double IsLiving::getCurrentArmor() const
{
	return m_ShipStats.m_Armor;
}
