#include "pch.h"
#include "PlayerShip.h"
#include "Ammunition.h"

void Ammunition::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_AnimatedSprite);
}

Ammunition::Ammunition(Configuration::TexturesWeaponry tex_id, const sf::Vector2f& boundaries, float deg_angle, float speed)
	: Entity(Configuration::textures_weaponry.get(tex_id)), m_DegAngle(deg_angle),
		m_Animation(&Configuration::textures_weaponry.get(tex_id)),
		m_Boundaries(boundaries)

{
	setRadAngle();
}



#pragma region SETTERS / GETTERS



// rotation in degrees, mods the value by 360
void Ammunition::setRotation(float angle)
{
	m_DegAngle = angle;
	m_DegAngle = fmod(m_DegAngle, 360.f);


	/* CAREFUL, 180 deg shift because that's what works for sprites, but for different it might not */
	m_AnimatedSprite.setRotation(m_DegAngle + 180.f);
	m_Sprite.setRotation(m_DegAngle + 180.f);
	setRadAngle();
}
// rotation in degrees, mods the value by 360
void Ammunition::rotate(float angle)
{
	m_DegAngle += angle;
	m_DegAngle = fmod(m_DegAngle, 360.f);


	/* CAREFUL, 180 deg shift because that's what works for sprites, but for different it might not */
	m_AnimatedSprite.setRotation(m_DegAngle + 180.f);
	m_Sprite.setRotation(m_DegAngle + 180.f);
	setRadAngle();
}


#pragma endregion


void Ammunition::update(const sf::Time& deltaTime)
{

	if (!m_MarkedForDeletion) {
		updateAnimation(deltaTime);
		updatePosition(deltaTime);
	}

	updateIndividualBehavior(deltaTime);

	if (!Helpers::CheckIfPointContainedInArea(m_Position, Configuration::boundaries))
		markForDeletion(false);
}



void Ammunition::updatePosition(const sf::Time& deltaTime)
{
	m_Direction.x = cosf(getRotationRad() + static_cast<float>(M_PIl) / 2.f);
	m_Direction.y = sinf(getRotationRad() + static_cast<float>(M_PIl) / 2.f);
	sf::Vector2f m_Velocity = m_Direction * m_Speed;

	m_Position += m_Velocity * deltaTime.asSeconds();

	m_AnimatedSprite.setPosition(m_Position);
	m_Sprite.setPosition(m_Position);

}

void Ammunition::setPosition(const sf::Vector2f& pos)
{
	Entity::setPosition(pos);
	m_AnimatedSprite.setPosition(pos);
}

