#pragma once
#include "Ammunition.h"

class Laser :
	public Ammunition
{
public:
	enum class Patterns { straight, swarm, };

private:
	void draw(sf::RenderTarget& target, sf::RenderStates) const override;

	Animation			m_DeathAnimation		{ &Configuration::textures_weaponry.get(Configuration::TexturesWeaponry::ammo_laser_hit) };
	AnimatedSprite		m_DeathAnimationSprite;
	sf::Sound			m_DeathSound			{ Configuration::sounds.get(Configuration::Sounds::laser_hit) };


	Patterns m_Pattern;


	void initAnimation() ;
	void updateIndividualBehavior(const sf::Time& deltaTime) override;
	void updateMovementPatters(const sf::Time& deltaTime);

	void onDeletion(bool playAnimation = false) override ;
	void updateDeathEvents(const sf::Time& deltaTime);


public:
	Laser(Configuration::TexturesWeaponry tex_id, const sf::Vector2f& boundaries, float deg_angle, float speed = 400.f, Patterns pattern = Patterns::straight);


	float dealDamage() override;
};
