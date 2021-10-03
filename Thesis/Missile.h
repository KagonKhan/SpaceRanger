#pragma once
#include "Ammunition.h"

class Missile :
	public Ammunition
{
private:
	void draw(sf::RenderTarget& target, sf::RenderStates) const override;

	const Entity*			m_Target			{ nullptr };
	float					m_RotationRadius	{ 0.5f };
	float					m_SeekingDistance	{ 400.f };
	float					m_FuelDuration		{ 5.f };

	void initAnimation();
	void initSprites(Configuration::TexturesWeaponry tex_id);

	void updateIndividualBehavior(const sf::Time& deltaTime) override;
	void updateTrackingSystem(const sf::Time& deltaTime);



public:
	Missile(Configuration::TexturesWeaponry tex_id, Configuration::TexturesWeaponry thrusters, const sf::Vector2f& boundaries, float deg_angle, float speed = 400.f);


	float dealDamage() override;
	void lockOnTarget(const Entity* target)				{		m_Target = target;		};
};


