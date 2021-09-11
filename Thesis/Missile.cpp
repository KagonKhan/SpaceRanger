#include "pch.h"
#include "Missile.h"

void Missile::draw(sf::RenderTarget& target, sf::RenderStates) const
{
	if (m_MarkedForDeletion)
		target.draw(m_DeathAnimationSprite);
	else {
		target.draw(m_AnimatedSprite);
		target.draw(m_Sprite);
	}

}


Missile::Missile(Configuration::TexturesWeaponry tex_id, Configuration::TexturesWeaponry thrusters, const sf::Vector2f& boundaries, float deg_angle, float speed)
	: Ammunition(thrusters, boundaries, deg_angle, speed), m_DeathAnimation(&Configuration::textures_weaponry.get(Configuration::TexturesWeaponry::ammo_missile_death_anim)),
	m_Target(nullptr), m_RotationRadius(0.5), m_SeekingDistance(400), m_FuelDuration(5.f),
	m_DeathSound(Configuration::sounds.get(Configuration::Sounds::missile_explosion))
{

	initAnimation();


	m_Sprite.setTexture(Configuration::textures_weaponry.get(tex_id), true);
	m_Sprite.setOrigin(m_Sprite.getGlobalBounds().width / 2.f, m_Sprite.getGlobalBounds().height / 2.f);
	m_Sprite.setScale(0.5f, 0.5f);
	m_Sprite.setPosition(m_Position);

}

Missile::~Missile()
{

}

void Missile::initAnimation()
{

	m_Animation.addFramesLine(16, 1, 0);

	m_AnimatedSprite.setAnimation(&m_Animation);
	m_AnimatedSprite.setOrigin(m_AnimatedSprite.getSize().x / 2.f, 0);
	m_AnimatedSprite.setScale(0.25f, 0.25f);
	m_AnimatedSprite.setFrameTime(sf::seconds(0.1f));
	m_AnimatedSprite.setColor(sf::Color::Yellow);
	m_AnimatedSprite.play();



	for(int i = 1; i <= 9; ++i)
		m_DeathAnimation.addFramesLine(9, 9, i);

	m_DeathAnimationSprite.setAnimation(&m_DeathAnimation);
	m_DeathAnimationSprite.setOrigin(m_DeathAnimationSprite.getSize() / 2.f);
	m_DeathAnimationSprite.setFrameTime(sf::seconds(0.0125f));
	m_DeathAnimationSprite.setRepeat(1);
	m_DeathAnimationSprite.setLoop(false);
	m_DeathAnimationSprite.pause();
}

void Missile::updateIndividualBehavior(const sf::Time& deltaTime)
{

	if (m_Target)
		updateTrackingSystem(deltaTime);

	if(m_MarkedForDeletion)
		updateDeathEvents(deltaTime);


}

void Missile::updateTrackingSystem(const sf::Time& deltaTime)
{
	m_FuelDuration -= deltaTime.asSeconds();

	if (m_FuelDuration >= 0) {
		sf::Vector2f tar_pos = m_Target->getPosition();
		sf::Vector2f mis_pos = getPosition();


		if (std::fabsf(tar_pos.x - mis_pos.x) < m_SeekingDistance && std::fabsf(tar_pos.y - mis_pos.y) < m_SeekingDistance) {

			sf::Vector2f A(m_Direction);
			sf::Vector2f B(tar_pos - mis_pos);

			if (Helpers::perpDot(A, B) < 0) {
				rotate(-m_RotationRadius);
			}
			else if (Helpers::perpDot(A, B) > 0) {
				rotate(m_RotationRadius);
			}
			else {
				if (Helpers::dot(A, B) < 0)
					;// missileVelocity.y *= -1;
			}
		}
	}
}

void Missile::updateDeathEvents(const sf::Time& deltaTime)
{
	if (m_DeathAnimationSprite.getStatus() == AnimatedSprite::Status::Playing)
		m_DeathAnimationSprite.update(deltaTime);


	if (m_DeathAnimationSprite.getStatus() == AnimatedSprite::Status::Stopped && m_DeathSound.getStatus() == sf::Sound::Status::Stopped)
		m_CanBeDeleted = true;
}

void Missile::onDeletion(bool playAnimation)
{
	if (playAnimation) {
		m_MarkedForDeletion = true;
		m_DeathAnimationSprite.setPosition(m_Position);
		m_DeathAnimationSprite.play();

		m_DeathSound.setPosition(m_Position.x, -m_Position.y, 0.f);
		m_DeathSound.setVolume(50);
		m_DeathSound.setAttenuation(1);
		m_DeathSound.setMinDistance(std::sqrt(200 * 200 + 300 * 300));
		m_DeathSound.play();
	}
	else m_CanBeDeleted = true;
}

void Missile::lockOnTarget(const Entity* target)
{
	m_Target = target;
}

float Missile::dealDamage()
{
	if (!m_MarkedForDeletion) {
		markForDeletion(true);
		return 50.f;
	}
	return 0.f;
}


