#pragma once
#include "Ammunition.h"

class Weapon :
	public Entity
{
protected:
	float m_FiringRate;
	float m_TimeSinceLastShot;
	float m_FiringDelay;

	bool m_IsWeaponActive;


	sf::Vector2f m_WeaponOffset;

	// Constant deletion on random indexes
	// If testing results in slow processing, I might think of custom containers
	std::vector<std::unique_ptr<Ammunition>> m_Shots;

	// TODO better containers exists for this job, implement them
	std::list<std::unique_ptr<sf::Sound>> m_Sounds;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override final;
	



	/* Maybe call this function every X seconds? */
	void deleteFinishedSounds();
	void updateTimings(const sf::Time& deltaTime);
	void updateBulletsAndCheckForDeletion(const sf::Time& deltaTime);
	void updateTrackingTarget(const sf::Time& deltaTime);



	virtual void createBullet() = 0;
	virtual void createSound() = 0;

	const Entity* m_Target;
public:
	Weapon(const Weapon&) = delete;
	Weapon& operator=(const Weapon&) = delete;

	Weapon(Configuration::Textures tex_id);

	float getSpriteRotation()const;
	void setSpriteRotation(float angle);
	void rotateSprite(float angle);
	void setWeaponOffset(const sf::Vector2f& offset);
	const sf::Vector2f& getWeaponOffset();

	/* Different behavior, becasue a weapon can have offset */
	void setPosition(const sf::Vector2f& pos) override;



	// shots/second
	void setFiringRate(float rate);
	
	void setTarget(const Entity* target);

	void setIsWeaponActive(bool isActive);

	void shoot();


	void update(const sf::Time& deltaTime);


};


class LaserTurret :
	public Weapon
{
private:
	virtual void createBullet() override;
	virtual void createSound() override;

public:
	LaserTurret(const LaserTurret&) = delete;
	LaserTurret& operator=(const LaserTurret&) = delete;

	LaserTurret(Configuration::Textures tex_id);

};

class MissileTurret :
	public Weapon
{
private:
	virtual void createBullet() override;
	virtual void createSound() override;

public:
	MissileTurret(const MissileTurret&) = delete;
	MissileTurret& operator=(const MissileTurret&) = delete;

	MissileTurret(Configuration::Textures tex_id);


};