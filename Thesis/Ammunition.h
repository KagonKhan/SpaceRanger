#pragma once
#include "Entity.h"
#include "CanCollide.h"
#include "AnimatedSprite.h"


class Weapon;
class Ammunition :
	public Entity,
	public CanCollide,
	private sf::NonCopyable
{
private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void setRadAngle() { m_RadAngle = m_DegAngle / 180.f * static_cast<float>(M_PIl); };
	void updateAnimation(const sf::Time& deltaTime){ m_AnimatedSprite.update(deltaTime); }
	void updatePosition(const sf::Time& deltaTime);

	virtual void initAnimation() = 0;
	virtual void updateIndividualBehavior(const sf::Time& deltaTime) = 0;
	virtual void onDeletion(bool playAnimation) = 0;

protected:
	float m_DegAngle;
	float m_RadAngle;

	bool m_CanBeDeleted{ false };
	bool m_MarkedForDeletion{ false };

	sf::Vector2f m_Boundaries;

	Animation m_Animation;
	AnimatedSprite m_AnimatedSprite;




public:
	Ammunition(Configuration::TexturesWeaponry tex_id, const sf::Vector2f& boundaries, float deg_angle, float speed);

	void update(const sf::Time& deltaTime) override;


	void setPosition(const sf::Vector2f& pos) override;
	void setSpeed(float speed){ m_Speed = speed; }
	float getRotation()const { return m_RadAngle; }
	float getRotationRad()const { return m_RadAngle; }
	float getSpriteRotation()const { return m_Sprite.getRotation(); }

	void setSpriteRotation(float angle){ m_Sprite.setRotation(angle); }
	void setRotation(float angle);
	void rotate(float angle);
	void rotateSprite(float angle){ m_Sprite.rotate(angle); }


	void markForDeletion(bool playAnimation = false) { onDeletion(playAnimation); };

	bool canBeDeleted()const {		return m_CanBeDeleted;	};
	virtual float dealDamage() = 0;
};
