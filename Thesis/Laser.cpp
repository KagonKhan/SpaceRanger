#include "pch.h"
#include "Laser.h"


void Laser::draw(sf::RenderTarget& target, sf::RenderStates) const
{
	if (m_MarkedForDeletion) {
		if (m_DeathAnimationSprite.getStatus() == AnimatedSprite::Status::Playing)
			target.draw(m_DeathAnimationSprite);
	}
	else {
		target.draw(m_AnimatedSprite);
	}
}

Laser::Laser(Configuration::TexturesWeaponry tex_id, const sf::Vector2f& boundaries, float deg_angle, float speed, Patterns pattern)
	: Ammunition(tex_id, boundaries, deg_angle, speed),
	m_DeathSound(Configuration::sounds.get(Configuration::Sounds::laser_hit)),
	m_DeathAnimation(&Configuration::textures_weaponry.get(Configuration::TexturesWeaponry::ammo_laser_hit)),
	m_Pattern(pattern)
{
	initAnimation();


	m_Speed = 1500.f;
}

void Laser::initAnimation()
{
	m_Animation.addFramesColumn(1, 3, 0);

	m_AnimatedSprite.setAnimation(&m_Animation);
	m_AnimatedSprite.setFrameTime(sf::seconds(0.2f));
	m_AnimatedSprite.setLoop(false);
	m_AnimatedSprite.setOrigin(m_AnimatedSprite.getSize() / 2.f);
	m_AnimatedSprite.play();






	m_DeathAnimation.addFramesLine(8, 1, 0);

	m_DeathAnimationSprite.setAnimation(&m_DeathAnimation);
	m_DeathAnimationSprite.setOrigin(m_DeathAnimationSprite.getSize() / 2.f);
	m_DeathAnimationSprite.setFrameTime(sf::seconds(0.0625f));
	m_DeathAnimationSprite.setRepeat(1);
	m_DeathAnimationSprite.setLoop(false);
	m_DeathAnimationSprite.pause();
	m_DeathAnimationSprite.setScale(0.15f, 0.15f);



}

void Laser::updateIndividualBehavior(const sf::Time& deltaTime)
{
	if (m_MarkedForDeletion)
		updateDeathEvents(deltaTime);

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

void Laser::onDeletion(bool playAnimation)
{
	if (playAnimation) {
		m_MarkedForDeletion = true;
		m_DeathAnimationSprite.setPosition(m_Position);
		m_DeathAnimationSprite.play();


		//TODO: Once done, uncomment
		/*m_DeathSound.setPosition(m_Position.x, -m_Position.y, 0.f);
		m_DeathSound.setVolume(60);
		m_DeathSound.setAttenuation(1);
		m_DeathSound.setMinDistance(std::sqrt(200 * 200 + 300 * 300));
		m_DeathSound.play();*/
	}
	else m_CanBeDeleted = true;
}

void Laser::updateDeathEvents(const sf::Time& deltaTime)
{
	if (m_DeathAnimationSprite.getStatus() == AnimatedSprite::Status::Playing)
		m_DeathAnimationSprite.update(deltaTime);

	if (m_DeathAnimationSprite.getStatus() == AnimatedSprite::Status::Stopped && m_DeathSound.getStatus() == sf::Sound::Status::Stopped)
		m_CanBeDeleted = true;
}

float Laser::dealDamage()
{
	if (!m_MarkedForDeletion) {
		markForDeletion(true);
		return 20.f;
	}
	return 0.f;
}
