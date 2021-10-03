#pragma once
#include "Weapon.h"

/* CAREFUL only beam turret holds parent reference, for now I only block player's ship's movement, might change some day */
class BeamTurret :
	public Weapon
{
private:
	void createBullet() override;
	void createSound() override;
	void updateIndividualBehavior(const sf::Time& deltaTime) override; 

	Entity::opt_ref m_Parent;

public:
	explicit BeamTurret(Entity::opt_ref parent = std::nullopt);
	explicit BeamTurret(Configuration::TexturesWeaponry tex_id, Entity::opt_ref parent = std::nullopt);


	void stop()				{		m_Shots.clear();	}
};