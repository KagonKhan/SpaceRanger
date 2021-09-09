#pragma once
#include "Ammunition.h"

class Laser :
	public Ammunition
{
private:
	void initAnimation() override;
	void updateIndividualBehavior(const sf::Time& deltaTime) override;

public:
	Laser(Configuration::TexturesWeaponry tex_id, const sf::Vector2f& boundaries, float deg_angle, float speed = 400.f);
	virtual ~Laser();

	float dealDamage();
};
