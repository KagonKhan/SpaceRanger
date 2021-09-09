#pragma once
#include "Weapon.h"
class LaserTurret :
	public Weapon
{
private:
	virtual void createBullet() override;
	virtual void createSound() override;
	virtual void updateIndividualBehavior(const sf::Time& deltaTime) override;

public:
	LaserTurret(Configuration::TexturesWeaponry tex_id);
	virtual ~LaserTurret();
};
