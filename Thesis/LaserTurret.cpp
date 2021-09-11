#include "pch.h"
#include "LaserTurret.h"
#include "Laser.h"

LaserTurret::LaserTurret(Configuration::TexturesWeaponry tex_id)
	: Weapon(tex_id)
{

}

LaserTurret::~LaserTurret()
{
}

void LaserTurret::createBullet()
{
	std::unique_ptr<Laser> shot(new Laser(Configuration::TexturesWeaponry::ammo_laser, Configuration::boundaries, -90, 1200));
	shot->setPosition(m_Position);
	shot->setRotation(m_Sprite.getRotation());


	m_Shots.push_back(std::move(shot));
}

void LaserTurret::createSound()
{
	std::unique_ptr<sf::Sound> sound(new sf::Sound(Configuration::sounds.get(Configuration::Sounds::laser)));
	float volume = 100.f * Configuration::m_MasterVolume / 100.f * Configuration::m_SoundEffectsVolume / 100.f;
	sound->setVolume(volume);

	sound->setAttenuation(1.f);
	sound->setPosition(m_Position.x, -m_Position.y, 0.f);
	sound->setMinDistance(std::sqrt(200 * 200 + 300 * 300));

	sound->play();



	m_Sounds.emplace_back(std::move(sound));
}

void LaserTurret::updateIndividualBehavior(const sf::Time& deltaTime)
{
}
