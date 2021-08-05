#pragma once
#include "Entity.h"

class Ship :
	public Entity
{
	double m_MaxHP, m_CurrentHP;

public:
	Ship(double max_hp, Configuration::Textures tex_id);
	virtual ~Ship();
};