#include "pch.h"
#include "IsLiving.h"


IsLiving::IsLiving(double max_hp, double armor, int plating)
	: m_CurrentHp(max_hp), m_MaxHp(max_hp),
		m_Armor(armor), m_Plating(plating),
		m_IsAlive(true)
{
}

IsLiving::~IsLiving()
{
	m_IsAlive = false;
}

void IsLiving::receiveDamage(double amount)
{
	m_CurrentHp -= amount;
	if (m_CurrentHp <= 0)
		IsLiving::~IsLiving();
}

bool IsLiving::isAlive() const
{
	return m_IsAlive;
}

double IsLiving::getCurrentHP() const
{
	return m_CurrentHp;
}

int IsLiving::getCurrentPlating() const
{
	return m_Plating;
}

double IsLiving::getCurrentArmor() const
{
	return m_Armor;
}
