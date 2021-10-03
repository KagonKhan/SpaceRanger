#include "pch.h"
#include "Missile.h"

void Missile::draw(sf::RenderTarget& target, sf::RenderStates) const
{

	if (m_OnDestroy.isMarkedForDeletion()) {
		target.draw(m_OnDestroy);
		return;
	}

	target.draw(m_AnimatedSprite);
	target.draw(m_Sprite);
	

}


Missile::Missile(Configuration::TexturesWeaponry tex_id, Configuration::TexturesWeaponry thrusters, const sf::Vector2f& boundaries, float deg_angle, float speed)
	: Ammunition(thrusters, boundaries, deg_angle, speed)
{
	initAnimation();
	initSprites(tex_id);

	m_Speed = 300.f;
}


void Missile::initAnimation()
{

	Animation::Line frames{ 16,1,0 };
	m_Animation.addFrames(frames);

	m_AnimatedSprite.setAnimation(&m_Animation);
	m_AnimatedSprite.setOrigin(m_AnimatedSprite.getSize().x / 2.f, 0);
	m_AnimatedSprite.setScale(0.25f, 0.25f);
	m_AnimatedSprite.setFrameTime(sf::seconds(0.1f));
	m_AnimatedSprite.setColor(sf::Color::Yellow);
	m_AnimatedSprite.play();

	sf::Texture* texture = &Configuration::textures_weaponry.get(Configuration::TexturesWeaponry::ammo_missile_death_anim);
	m_OnDestroy.initAnimation(texture, Animation::Line{ 9,9,0 }, sf::seconds(0.0125f), sf::Vector2f{1.f,1.f });

	m_OnDestroy.initSound(Configuration::sounds.get(Configuration::Sounds::missile_explosion));
	for(int i = 1; i <= 9; ++i)
		m_OnDestroy.addFrames(Animation::Line{ 9,9,i });
		
}

void Missile::initSprites(Configuration::TexturesWeaponry tex_id)
{
	m_Sprite.setTexture(Configuration::textures_weaponry.get(tex_id), true);
	m_Sprite.setOrigin(m_Sprite.getGlobalBounds().width / 2.f, m_Sprite.getGlobalBounds().height / 2.f);
	m_Sprite.setScale(0.5f, 0.5f);
	m_Sprite.setPosition(m_Position);
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


float Missile::dealDamage()
{
	if (!m_OnDestroy.isMarkedForDeletion()) {
		m_OnDestroy.start();
		return 50.f;
	}
	return 0.f;
}


