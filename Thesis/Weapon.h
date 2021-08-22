#pragma once
#include "Ammunition.h"

class Weapon :
	public Entity
{
protected:
	float m_FiringRate;
	float m_TimeSinceLastShot;


	// Constant deletion on random indexes
	// If testing results in slow processing, I might think of custom containers

	std::vector<Ammunition*> m_Shots;

	const Entity* m_Target;
public:
	Weapon(const Weapon&) = delete;
	Weapon& operator=(const Weapon&) = delete;

	Weapon(Configuration::Textures tex_id);

	// shots/second
	void setFiringRate(float rate);
	
	void setTarget(const Entity* target);

	virtual void shoot() = 0;


	float getSpriteRotation()const;
	void setSpriteRotation(float angle);
	void rotateSprite(float angle);

};


class LaserTurret :
	public Weapon
{
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override final;

public:
	LaserTurret(const LaserTurret&) = delete;
	LaserTurret& operator=(const LaserTurret&) = delete;

	LaserTurret(Configuration::Textures tex_id);

	void shoot();
	void update(const sf::Time& deltatime) override;
};