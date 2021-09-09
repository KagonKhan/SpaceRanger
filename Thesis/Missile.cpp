#include "pch.h"
#include "Missile.h"

Missile::Missile(Configuration::TexturesWeaponry tex_id, Configuration::TexturesWeaponry thrusters, const sf::Vector2f& boundaries, float deg_angle, float speed)
	: Ammunition(thrusters, boundaries, deg_angle, speed),
	m_Target(nullptr), m_RotationRadius(0.5), m_SeekingDistance(400), m_FuelDuration(5.f)
{
	initAnimation();


	m_Sprite.setTexture(Configuration::textures_weaponry.get(tex_id), true);
	m_Sprite.setOrigin(m_Sprite.getGlobalBounds().width / 2.f, m_Sprite.getGlobalBounds().height / 2.f);
	m_Sprite.setScale(0.5f, 0.5f);
	m_Sprite.setPosition(m_Position);

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
}

void Missile::updateIndividualBehavior(const sf::Time& deltaTime)
{

	if (m_Target)
		updateTrackingSystem(deltaTime);
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

void Missile::draw(sf::RenderTarget& target, sf::RenderStates states) const
{

	target.draw(m_AnimatedSprite);
	target.draw(m_Sprite);
}

void Missile::lockOnTarget(const Entity* target)
{
	m_Target = target;
}

float Missile::dealDamage()
{
	return 50.f;
}


