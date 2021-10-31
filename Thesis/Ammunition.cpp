#include "pch.h"
#include "PlayerShip.h"
#include "Ammunition.h"

Ammunition::Ammunition(Configuration::TexturesWeaponry tex_id, const sf::Vector2f& boundaries, float deg_angle, float speed)
	: Entity(Configuration::textures_weaponry.get(tex_id)), m_DegAngle(deg_angle),
		m_Boundaries(boundaries),
		m_Animation(&Configuration::textures_weaponry.get(tex_id)),
		m_OnDestroy(*this)
{
	setRadAngle();
}

Ammunition::~Ammunition()
{

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

void Ammunition::setPosition(const sf::Vector2f& pos)
{
	Entity::setPosition(pos);
	m_AnimatedSprite.setPosition(pos);
}

void Ammunition::move(sf::Vector2f moveBy)
{
	Entity::setPosition(m_Position + moveBy);
	m_AnimatedSprite.move(moveBy);
}

#pragma endregion


void Ammunition::update(const sf::Time& deltaTime)
{
	if (m_OnDestroy.isMarkedForDeletion()) {
		m_OnDestroy.update(deltaTime);
		return;
	}


	updateAnimation(deltaTime);
	updatePosition(deltaTime);


	updateIndividualBehavior(deltaTime);

	auto a = Configuration::boundaries;
	const auto area = sf::FloatRect(-a/5.f, a * 1.5f);
	if (!Helpers::CheckIfPointContainedInArea(m_Position, area) && !m_OnDestroy.isMarkedForDeletion())
		m_OnDestroy.start(true);
}



void Ammunition::updatePosition(const sf::Time& deltaTime)
{
	m_Direction.x = cosf(getRotationRad() + static_cast<float>(M_PIl) / 2.f);
	m_Direction.y = sinf(getRotationRad() + static_cast<float>(M_PIl) / 2.f);
	Helpers::normalize(m_Direction);
	sf::Vector2f m_Velocity = m_Direction * m_Speed;

	move(m_Velocity * deltaTime.asSeconds());
}


