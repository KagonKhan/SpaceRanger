#pragma once
#include "Weapon.h"

class MissileTurret :
	public Weapon
{
private:
	virtual void createBullet() override;
	virtual void createSound() override;
	virtual void updateIndividualBehavior(const sf::Time& deltaTime) override;

public:
	MissileTurret(Configuration::TexturesWeaponry tex_id);
	virtual ~MissileTurret();
};