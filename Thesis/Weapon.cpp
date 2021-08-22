#include "pch.h"

#include "Weapon.h"
#include "Entity.h"

Weapon::Weapon(Configuration::Textures tex_id)
	: Entity(tex_id), m_Target(nullptr), m_FiringRate(0), m_TimeSinceLastShot(0)
{
}

void Weapon::setFiringRate(float rate)
{
	m_FiringRate=rate;

}

void Weapon::setTarget(const Entity* target)
{
	m_Target = target;
}

void Weapon::shoot()
{
	
}

float Weapon::getSpriteRotation() const
{
	return m_Sprite.getRotation();
}

void Weapon::setSpriteRotation(float angle)
{
	m_Sprite.setRotation(angle);
}

void Weapon::rotateSprite(float angle)
{
	m_Sprite.rotate(angle);
}

/* =============================    Laser Turret    ========================= */

void LaserTurret::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_Sprite);

	for (Ammunition* shot : m_Shots)
		target.draw(*shot);
}

LaserTurret::LaserTurret(Configuration::Textures tex_id)
	: Weapon(tex_id)
{

}

void LaserTurret::shoot()
{
	/* TODO maybe hold shot delay, instead of calculating each time */
	if (m_TimeSinceLastShot > 1 / m_FiringRate) {
		m_Shots.push_back(new Laser(Configuration::Textures::Ammo_Laser, -90, 400 ));
		m_Shots.back()->setPosition(m_Position);

		m_TimeSinceLastShot = 0;
	}
}

void LaserTurret::update(const sf::Time& deltatime)
{
	m_TimeSinceLastShot += deltatime.asSeconds();


	for (Ammunition* shot : m_Shots)
		shot->update(deltatime);

	// if targeted, aim
	if (m_Target) {


	}
}
