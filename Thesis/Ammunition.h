#pragma once
#include "Entity.h"
#include "CanCollide.h"
#include "AnimatedSprite.h"

# define M_PIl          3.141592653589793238462643383279502884L /* pi */

class Weapon;
class Ammunition :
	public Entity,
	public CanCollide,
	private sf::NonCopyable
{
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void setRadAngle();
	void updateAnimation(const sf::Time& deltaTime);
	void updatePosition(const sf::Time& deltaTime);

	virtual void initAnimation() = 0;
	virtual void updateIndividualBehavior(const sf::Time& deltaTime) = 0;
	virtual void onDeletion(bool playAnimation) = 0;

protected:
	float m_Speed, m_DegAngle, m_RadAngle;

	bool m_CanBeDeleted;
	bool m_MarkedForDeletion;

	sf::Vector2f m_Boundaries;

	Animation m_Animation;
	AnimatedSprite m_AnimatedSprite;




public:
	Ammunition(Configuration::TexturesWeaponry tex_id, const sf::Vector2f& boundaries, float deg_angle, float speed);
	virtual ~Ammunition();

	void update(const sf::Time& deltaTime) override;

#pragma region SETTERS / GETTERS
	void setPosition(const sf::Vector2f& pos) override;
	float getRotation()const;
	float getRotationRad()const;
	float getSpriteRotation()const;

	void setSpriteRotation(float angle);
	void setRotation(float angle);
	void rotate(float angle);
	void rotateSprite(float angle);
#pragma endregion

	void markForDeletion(bool playAnimation = false);

	bool canBeDeleted();
	virtual float dealDamage() = 0;
};
