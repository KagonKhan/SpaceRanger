#include "pch.h"
#include "Laser.h"


void Laser::draw(sf::RenderTarget& target, sf::RenderStates) const
{
	if (m_OnDestroy.isMarkedForDeletion()) {
		target.draw(m_OnDestroy);
		return;
	}
	
	target.draw(m_AnimatedSprite);
	
}

Laser::Laser(Configuration::TexturesWeaponry tex_id, const sf::Vector2f& boundaries, float deg_angle, float speed, Patterns pattern)
	: Ammunition(tex_id, boundaries, deg_angle, speed),
	m_Pattern(pattern)
{
	initAnimation();


	m_Speed = 1500.f;
}

void Laser::initAnimation()
{
	Animation::Column frames{ 1,3,0 };
	m_Animation.addFrames(frames);

	m_AnimatedSprite.setAnimation(&m_Animation);
	m_AnimatedSprite.setFrameTime(sf::seconds(0.2f));
	m_AnimatedSprite.setLoop(false);
	m_AnimatedSprite.setOrigin(m_AnimatedSprite.getSize() / 2.f);
	m_AnimatedSprite.play();


	sf::Texture* texture = &Configuration::textures_weaponry.get(Configuration::TexturesWeaponry::ammo_laser_hit);
	m_OnDestroy.initAnimation(texture, Animation::Line{ 8,1,0 }, sf::seconds(0.0625f), sf::Vector2f{ 0.15f,0.15f });

	m_OnDestroy.initSound(Configuration::sounds.get(Configuration::Sounds::laser_hit));

}

void Laser::updateIndividualBehavior(const sf::Time& deltaTime)
{

	updateMovementPatters(deltaTime);
}

void Laser::updateMovementPatters(const sf::Time& deltaTime)
{		
	switch (m_Pattern) {
	case Patterns::straight:													break;
	case Patterns::swarm:		rotate(Helpers::getRandom(-2.f, 2.f));			break;
	default:																	break;
	}
	
}

float Laser::dealDamage()
{
	if (!m_OnDestroy.isMarkedForDeletion()) {
		m_OnDestroy.start();
		return 200.f;
	}
	return 0.f;
}
