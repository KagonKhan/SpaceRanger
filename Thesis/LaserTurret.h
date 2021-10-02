#pragma once
#include "Weapon.h"
#include "Laser.h"
class LaserTurret :
	public Weapon
{
private:
	void createBullet() override;
	void createSound() override;
	void updateIndividualBehavior(const sf::Time& deltaTime) override;

	Laser::Patterns m_Pattern;

public:
	explicit LaserTurret();
	explicit LaserTurret(Configuration::TexturesWeaponry tex_id);
	virtual ~LaserTurret();

	void setPattern(Laser::Patterns pattern);
};
