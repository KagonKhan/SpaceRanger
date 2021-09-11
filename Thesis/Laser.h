#pragma once
#include "Ammunition.h"

class Laser :
	public Ammunition
{
private:
	void draw(sf::RenderTarget& target, sf::RenderStates) const override final;

	Animation m_DeathAnimation;
	AnimatedSprite m_DeathAnimationSprite;
	sf::Sound m_DeathSound;

	enum class Patterns;
	Patterns m_Pattern;


	void initAnimation() override;
	void updateIndividualBehavior(const sf::Time& deltaTime) override;
	void updateMovementPatters(const sf::Time& deltaTime);

	void onDeletion(bool playAnimation = false) override ;
	void updateDeathEvents(const sf::Time& deltaTime);


public:
	Laser(Configuration::TexturesWeaponry tex_id, const sf::Vector2f& boundaries, float deg_angle, float speed = 400.f, Patterns pattern = Patterns::straight);
	virtual ~Laser();

	float dealDamage();
	enum class Patterns { straight, swarm, };
};
