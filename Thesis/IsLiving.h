#pragma once


class IsLiving
{
private:
	struct ShipStats {
		float		m_CurrentHp;
		float		m_MaxHp;
		int			m_Armor; // % lower received dmg
		int			m_Plating; // Completely negate n instances of damage
		bool		m_IsAlive;
	};
	ShipStats		m_ShipStats;


public: 
	IsLiving(float max_hp, int armor = 1, int plating = 0);
	virtual ~IsLiving() = default;


	// Potentially virtual to allow for modification
	// Maybe usage of std::function? some fancy stuff
	virtual void receiveDamage(float amount);




	bool isAlive()				const	{		return m_ShipStats.m_IsAlive;		}
	double getHP()				const	{		return m_ShipStats.m_CurrentHp;		}
	int getPlating()			const	{		return m_ShipStats.m_Plating;		}
	double getArmor()			const	{		return m_ShipStats.m_Armor;			}
	ShipStats& getShipStats()			{		return m_ShipStats;					}
};