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

	Laser::Patterns m_Pattern{ Laser::Patterns::straight };

public:
	explicit LaserTurret();
	explicit LaserTurret(Configuration::TexturesWeaponry tex_id);

	void setPattern(Laser::Patterns pattern);
};
