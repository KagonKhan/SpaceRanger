#pragma once
#include "Entity.h"
#include "CanCollide.h"
#include "AnimatedSprite.h"
#include "OnDestroy.h"

class Weapon; 
class Ammunition :
	public Entity,
	public CanCollide,
	private sf::NonCopyable
{
private:
	void draw(sf::RenderTarget& target, sf::RenderStates) const override	{		target.draw(m_AnimatedSprite);									}
	void updateAnimation(const sf::Time& deltaTime)							{		m_AnimatedSprite.update(deltaTime);								}
	void setRadAngle()														{		m_RadAngle = m_DegAngle / 180.f * static_cast<float>(M_PIl);	}

	void updatePosition(const sf::Time& deltaTime);

	virtual void updateIndividualBehavior(const sf::Time& deltaTime) = 0;
	 
protected:
	float m_DegAngle;
	float m_RadAngle;

	sf::Vector2f m_Boundaries;

	Animation m_Animation;
	AnimatedSprite m_AnimatedSprite;

	OnDestroy m_OnDestroy;

public:
	Ammunition(Configuration::TexturesWeaponry tex_id, const sf::Vector2f& boundaries, float deg_angle, float speed);
	~Ammunition()override;


	void update(const sf::Time& deltaTime) override;

	virtual float dealDamage() = 0;

	void setPosition(const sf::Vector2f& pos) override;
	void move(sf::Vector2f moveBy);

	void setRotation(float angle);
	void rotate(float angle);

	bool canBeDeleted()	const								{			return m_OnDestroy.canBeDeleted();	}
	void setSpeed(float speed)								{			m_Speed = speed;					}
	void setSpriteRotation(float angle)						{			m_Sprite.setRotation(angle);		}
	void rotateSprite(float angle)							{			m_Sprite.rotate(angle);				}
	float getRotation() const								{			return m_DegAngle;					}
	float getRotationRad() const							{			return m_RadAngle;					}
	float getSpriteRotation() const							{			return m_Sprite.getRotation();		}
};
