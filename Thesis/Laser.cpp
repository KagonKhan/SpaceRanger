#include "pch.h"
#include "Laser.h"


Laser::Laser(Configuration::TexturesWeaponry tex_id, const sf::Vector2f& boundaries, float deg_angle, float speed)
	: Ammunition(tex_id, boundaries, deg_angle, speed)

{
	initAnimation();
}

void Laser::initAnimation()
{
	m_Animation.addFramesColumn(1, 3, 0);

	m_AnimatedSprite.setAnimation(&m_Animation);
	m_AnimatedSprite.setFrameTime(sf::seconds(0.2f));
	m_AnimatedSprite.setLoop(false);
	m_AnimatedSprite.setOrigin(m_AnimatedSprite.getSize() / 2.f);
	m_AnimatedSprite.play();
}

void Laser::updateIndividualBehavior(const sf::Time& deltaTime)
{
}

Laser::~Laser()
{

}

float Laser::dealDamage()
{
	return 10.f;
}

