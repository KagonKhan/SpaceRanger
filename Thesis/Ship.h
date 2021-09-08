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
	void draw(sf::RenderTarget& target, sf::RenderStates) const override;

protected:
	enum class WeaponType { Laser, Missile, Beam };

	void initWeapon(const sf::Vector2f& offset, float firing_rate, WeaponType weapon_type, float rotation = 180.f);

public:
	Ship(double max_hp, Configuration::TexturesShips tex_id);
	virtual ~Ship();


	void setPosition(const sf::Vector2f& pos) override;
	void setPosition(float x, float y) override;

};