#pragma once
#include "Ammunition.h"

class Missile :
	public Ammunition
{
private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override final;

	const Entity* m_Target;
	float m_RotationRadius;
	float m_SeekingDistance;
	float m_FuelDuration;

	Animation m_DeathAnimation;
	AnimatedSprite m_DeathAnimationSprite;
	sf::Sound m_DeathSound;

	void initAnimation() override;
	void updateIndividualBehavior(const sf::Time& deltaTime) override final;
	void updateTrackingSystem(const sf::Time& deltaTime);

	void onDeletion(bool playAnimation = false) override;
public:
	Missile(Configuration::TexturesWeaponry tex_id, Configuration::TexturesWeaponry thrusters, const sf::Vector2f& boundaries, float deg_angle, float speed = 400.f);
	virtual ~Missile();

	void lockOnTarget(const Entity* target);
	float dealDamage();
};


