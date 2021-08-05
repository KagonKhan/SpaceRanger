#include "pch.h"
#include "Ship.h"

Ship::Ship(double max_hp, Configuration::Textures tex_id)
	: Entity(tex_id), m_MaxHP(max_hp), m_CurrentHP(max_hp)
{
}

Ship::~Ship()
{
}
