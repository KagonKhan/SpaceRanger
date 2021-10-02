#include "pch.h"
#include "PlayerShip.h"
#include "Ammunition.h"

void Ammunition::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_AnimatedSprite);
}

Ammunition::Ammunition(Configuration::TexturesWeaponry tex_id, const sf::Vector2f& boundaries, float deg_angle, float speed)
	: Entity(Configuration::textures_weaponry.get(tex_id)), m_DegAngle(deg_angle),m_Speed(speed),
		m_Animation(&Configuration::textures_weaponry.get(tex_id)),
		m_Boundaries(boundaries), m_CanBeDeleted(false), m_MarkedForDeletion(false)

{
	setRadAngle();
}

Ammunition::~Ammunition()
{

}



#pragma region SETTERS / GETTERS


// rotation in degrees
float Ammunition::getRotation() const
{
	return m_RadAngle;
}
float Ammunition::getRotationRad() const
{
	return m_RadAngle;
}

void Ammunition::setRadAngle()
{
	m_RadAngle = m_DegAngle / 180.f * M_PIl;
}


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
// rotation in degrees
float Ammunition::getSpriteRotation() const
{
	return m_Sprite.getRotation();
}
// rotation in degrees
void Ammunition::setSpriteRotation(float angle)
{
	m_Sprite.setRotation(angle);
}
// rotation in degrees
void Ammunition::rotateSprite(float angle)
{
	m_Sprite.rotate(angle);
}

#pragma endregion

void Ammunition::markForDeletion(bool playAnimation)
{
	onDeletion(playAnimation);
}

bool Ammunition::canBeDeleted()
{
	return m_CanBeDeleted;
}
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


void Ammunition::updateAnimation(const sf::Time& deltaTime)
{
	m_AnimatedSprite.update(deltaTime);
}

void Ammunition::updatePosition(const sf::Time& deltaTime)
{
	m_Direction.x = cosf(getRotationRad() + M_PIl / 2.f);
	m_Direction.y = sinf(getRotationRad() + M_PIl / 2.f);
	sf::Vector2f m_Velocity = m_Direction * m_Speed;

	m_Position += m_Velocity * deltaTime.asSeconds();

	m_AnimatedSprite.setPosition(m_Position);
	m_Sprite.setPosition(m_Position);

}

void Ammunition::setPosition(const sf::Vector2f& pos)
{
	m_Position = pos;
	m_Sprite.setPosition(pos);
	m_AnimatedSprite.setPosition(pos);
}

void Ammunition::setSpeed(float speed)
{
	m_Speed = speed;
}
