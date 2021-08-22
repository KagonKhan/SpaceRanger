#pragma once
#include "Entity.h"
#include "IsLiving.h"
#include "HasWeapons.h"
#include "CanCollide.h"

class Ship :
	public Entity,
	public IsLiving,
	public HasWeapons,
	public CanCollide
{
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;


public:
	Ship(double max_hp, Configuration::Textures tex_id);
	virtual ~Ship();

	virtual void update(const sf::Time& deltaTime) = 0;
};