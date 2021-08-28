#pragma once


class IsLiving
{
private:
	struct ShipStats {
	public:
		double m_CurrentHp, m_MaxHp;
		int m_Armor; // % lower received dmg
		int m_Plating; // Completely negate n instances of damage

		bool m_IsAlive;
	} m_ShipStats;


public:
	IsLiving(IsLiving&) = delete;
	IsLiving& operator=(IsLiving&) = delete;

	IsLiving(double max_hp, int armor = 1, int plating = 0);
	virtual ~IsLiving();


	// Potentially virtual to allow for modification
	// Maybe usage of std::function? some fancy shit
	virtual void receiveDamage(double amount);

	bool isAlive() const;
	double getCurrentHP() const;
	int getCurrentPlating() const;
	double getCurrentArmor() const;

	ShipStats& getShipStats();
};