#pragma once
#include "Ammunition.h"

class Weapon :
	public Entity,
	private sf::NonCopyable
{
protected:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const final;

	float			m_FiringRate			{ 0 };
	float			m_TimeSinceLastShot		{ 0 };
	float			m_FiringDelay			{ 0 };
	bool			m_IsWeaponActive		{ false };
	const Entity*	m_Target				{ nullptr };


	// Constant deletion on random indexes
	// If testing results in slow processing, I might think of custom containers
	std::vector<std::unique_ptr<Ammunition>> m_Shots;

	std::queue<std::unique_ptr<sf::Sound>> m_Sounds;

	
	/* Maybe call this function every X seconds? */
	void deleteFinishedSounds();

	void updateTimings(const sf::Time& deltaTime)						{ m_TimeSinceLastShot += deltaTime.asSeconds(); }
	void updateBulletsAndCheckForDeletion(const sf::Time& deltaTime);
	void updateTrackingTarget(const sf::Time& deltaTime);
	virtual void updateIndividualBehavior(const sf::Time& deltaTime) = 0;



	virtual void createBullet() = 0;
	virtual void createSound() = 0;

	std::vector<Ammunition*> ammoOnScreen;


public:
	explicit Weapon(Configuration::TexturesWeaponry tex_id);

	using ptr = std::unique_ptr<Weapon>;

	void shoot(bool makeSound = true);
	void update(const sf::Time& deltaTime) override ;
	std::vector<Ammunition*>& getAmmoOnScreen();

	// shots/second
	void setFiringRate(float rate);



	void setSpriteRotation(float angle)					{		m_Sprite.setRotation(angle);		}
	void rotateSprite(float angle)						{		m_Sprite.rotate(angle);				}
	void setIsWeaponActive(bool isActive)				{		m_IsWeaponActive = isActive;		}
	virtual void setTarget(const Entity* target)		{		m_Target = target;					}
	float getSpriteRotation()const						{		return m_Sprite.getRotation();		}
	bool isActive()const								{		return m_IsWeaponActive;			}

};



