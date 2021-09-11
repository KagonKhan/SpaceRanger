#pragma once
#include "Weapon.h"
#include "Laser.h"
class LaserTurret :
	public Weapon
{
private:
	virtual void createBullet() override;
	virtual void createSound() override;
	virtual void updateIndividualBehavior(const sf::Time& deltaTime) override;

	Laser::Patterns m_Pattern;

public:
	LaserTurret(Configuration::TexturesWeaponry tex_id);
	virtual ~LaserTurret();

	void setPattern(Laser::Patterns pattern);
};
