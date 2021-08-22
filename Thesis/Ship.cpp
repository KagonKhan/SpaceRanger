#include "pch.h"
#include "Ship.h"

void Ship::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_Sprite);
	target.draw(m_Shape);
}

Ship::Ship(double max_hp, Configuration::Textures tex_id)
	: Entity(tex_id), IsLiving(max_hp), HasWeapons(), CanCollide()
{
}

Ship::~Ship()
{
}
