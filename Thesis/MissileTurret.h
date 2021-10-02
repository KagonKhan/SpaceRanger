#pragma once
#include "Weapon.h"

class MissileTurret :
	public Weapon
{
private:
	void createBullet() override;
	void createSound() override;
	void updateIndividualBehavior(const sf::Time& deltaTime) override;

public:
	explicit MissileTurret();
	explicit MissileTurret(Configuration::TexturesWeaponry tex_id);
	virtual ~MissileTurret();
};