#pragma once
#include "Weapon.h"

/* CAREFUL only beam turret holds parent reference, for now I only block player's ship's movement, might change some day */
class BeamTurret :
	public Weapon
{
private:
	virtual void createBullet() override;
	virtual void createSound() override;
	virtual void updateIndividualBehavior(const sf::Time& deltaTime) override; 

	std::optional<std::reference_wrapper<Entity>> m_Parent;

public:
	BeamTurret(Configuration::TexturesWeaponry tex_id, Entity::opt_ref parent = std::nullopt);
	virtual ~BeamTurret();
};