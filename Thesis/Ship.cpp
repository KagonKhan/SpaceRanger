#include "pch.h"
#include "Ship.h"

void Ship::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_Sprite);
	target.draw(m_Shape);
}

Ship::Ship(double max_hp, Configuration::TexturesShips tex_id)
	: Entity(Configuration::textures_ships.get(tex_id)), IsLiving(max_hp), HasWeapons(), CanCollide()
{
}

Ship::~Ship()
{
}
