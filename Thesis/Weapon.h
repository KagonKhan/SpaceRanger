#pragma once
#include "Ammunition.h"

class Weapon :
	public Entity,
	private sf::NonCopyable
{
protected:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override final;

	float m_FiringRate, m_TimeSinceLastShot, m_FiringDelay;

	bool m_IsWeaponActive;

	// Constant deletion on random indexes
	// If testing results in slow processing, I might think of custom containers
	std::vector<std::unique_ptr<Ammunition>> m_Shots;

	std::queue<std::unique_ptr<sf::Sound>> m_Sounds;

	const Entity* m_Target;
	
	/* Maybe call this function every X seconds? */
	void deleteFinishedSounds();

	void updateTimings(const sf::Time& deltaTime);
	void updateBulletsAndCheckForDeletion(const sf::Time& deltaTime);
	void updateTrackingTarget(const sf::Time& deltaTime);
	virtual void updateIndividualBehavior(const sf::Time& deltaTime) = 0;



	virtual void createBullet() = 0;
	virtual void createSound() = 0;

	std::vector<Ammunition*> ghostPTR;


public:
	Weapon(Configuration::TexturesWeaponry tex_id);
	virtual ~Weapon();

	void setIsWeaponActive(bool isActive);
	bool isActive();
	bool shoot();
	void update(const sf::Time& deltaTime) override final;

	std::vector<Ammunition*>& getShots();


#pragma region SETTERS / GETTERS
	float getSpriteRotation()const;
	void setSpriteRotation(float angle);
	void rotateSprite(float angle);

	/* Different behavior, becasue a weapon can have offset */
	void setPosition(const sf::Vector2f& pos) override;
	void setPosition(float x, float y) override;
	// shots/second
	void setFiringRate(float rate);
	virtual void setTarget(const Entity* target);
#pragma endregion
};



