#pragma once


class IsLiving
{
private:
	double m_CurrentHp, m_MaxHp;
	double m_Armor; // % lower received dmg
	int m_Plating; // Completely negate x instances of damage

	bool m_IsAlive;

public:
	IsLiving(IsLiving&) = delete;
	IsLiving& operator=(IsLiving&) = delete;

	IsLiving(double max_hp, double armor = 1, int plating = 0);
	virtual ~IsLiving();


	// Potentially virtual to allow for modification
	// Maybe usage of std::function? some fancy shit
	virtual void receiveDamage(double amount);

	bool isAlive() const;
	double getCurrentHP() const;
	int getCurrentPlating() const;
	double getCurrentArmor() const;
};