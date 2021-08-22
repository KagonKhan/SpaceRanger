#include "pch.h"

#include "Ammunition.h"


void Ammunition::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_Sprite);
}

void Ammunition::setRadAngle()
{
	m_RadAngle = m_DegAngle / 180.f * M_PIl;
}

Ammunition::Ammunition(Configuration::Textures tex_id, float deg_angle, float speed)
	:Entity(tex_id), m_DegAngle(deg_angle),m_Speed(speed)
{
	std::cout << "Ammunition class\n";

	setRadAngle();
	/* CAREFUL, Sprite angle 0 might point upwards, but here assumed 0 is pointing right */
	m_Direction.x = cosf(getRotationRad());
	m_Direction.y = sinf(getRotationRad());

	m_Velocity = m_Direction * m_Speed;
}
// rotation in degrees
float Ammunition::getRotation() const
{
	return m_RadAngle;
}
float Ammunition::getRotationRad() const
{
	return m_RadAngle;
}
// rotation in degrees, mods the value by 360
void Ammunition::setRotation(float angle)
{
	m_DegAngle = angle;
	m_DegAngle = fmod(m_DegAngle, 360.f);

	setRadAngle();
}
// rotation in degrees, mods the value by 360
void Ammunition::rotate(float angle)
{
	m_DegAngle += angle;
	m_DegAngle = fmod(m_DegAngle, 360.f);

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




/* ==============================    LASER    ============================== */

Laser::Laser(Configuration::Textures tex_id, float deg_angle, float speed)
	: Ammunition(tex_id, deg_angle, speed)
{

}

void Laser::update(const sf::Time& deltatime)
{
	m_Sprite.move(m_Velocity * deltatime.asSeconds());
	m_Position = m_Sprite.getPosition();
}

Rocket::Rocket(Configuration::Textures tex_id, float deg_angle, float speed)
	: Ammunition(tex_id, deg_angle, speed), m_Target(nullptr)
{

}

void Rocket::lockOnTarget(Entity* target)
{
	m_Target = target;
}

void Rocket::update(const sf::Time& deltatime)
{
	m_Sprite.move(m_Velocity * deltatime.asSeconds());
	m_Position = m_Sprite.getPosition();
}

Beam::Beam(Configuration::Textures tex_id, float deg_angle, float speed)
	:Ammunition(tex_id, deg_angle, speed)
{
}

void Beam::update(const sf::Time& deltatime)
{
	/* TODO animation update*/
}
