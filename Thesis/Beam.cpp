#include "pch.h"
#include "Beam.h"

Beam::Beam(Configuration::TexturesWeaponry tex_id, const sf::Vector2f& boundaries, float deg_angle, float speed)
	: Ammunition(tex_id, boundaries, deg_angle, speed)
{
	initAnimation();

	m_Speed = 0;
}


void Beam::initAnimation()
{
	m_Animation.addFrames(Animation::Line{ 11,1,0 });

	m_AnimatedSprite.setAnimation(&m_Animation);
	m_AnimatedSprite.setOrigin(sf::Vector2f(m_AnimatedSprite.getSize().x / 2.f, m_AnimatedSprite.getSize().y - 35));
	m_AnimatedSprite.setLoop(false);
	m_AnimatedSprite.setFrameTime(sf::seconds(0.05f));
	m_AnimatedSprite.setRepeat(3);
	m_AnimatedSprite.setScale(1.5f, 4.f);
	m_AnimatedSprite.setRotation(180);

	m_AnimatedSprite.play();
}

void Beam::updateIndividualBehavior(const sf::Time& deltaTime)
{
	if (m_AnimatedSprite.getStatus() != AnimatedSprite::Status::Playing)
		m_OnDestroy.start(true);
}

float Beam::dealDamage()
{

	if (m_DamageTick.getElapsedTime() > sf::seconds(0.2f)) {
		BOOST_LOG_TRIVIAL(info) << "Damage tick";
		m_DamageTick.restart();
		return 10.f;
	}
	
}
