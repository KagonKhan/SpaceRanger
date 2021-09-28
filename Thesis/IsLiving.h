#pragma once


class IsLiving
{
private:
	struct ShipStats {
		float m_CurrentHp;
		float m_MaxHp;
		int m_Armor; // % lower received dmg
		int m_Plating; // Completely negate n instances of damage

		bool m_IsAlive;
	};
	ShipStats m_ShipStats;


public: 
	IsLiving(IsLiving&) = delete;
	IsLiving& operator=(IsLiving&) = delete;

	IsLiving(float max_hp, int armor = 1, int plating = 0);
	virtual ~IsLiving();


	// Potentially virtual to allow for modification
	// Maybe usage of std::function? some fancy shit
	virtual void receiveDamage(float amount);

	bool isAlive() const;
	double getCurrentHP() const;
	int getCurrentPlating() const;
	double getCurrentArmor() const;

	virtual void onDestroy() = 0;

	ShipStats& getShipStats();
};