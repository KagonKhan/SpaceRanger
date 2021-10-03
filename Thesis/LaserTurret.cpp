#include "pch.h"
#include "LaserTurret.h"
#include "Laser.h"

LaserTurret::LaserTurret()
	: LaserTurret(Configuration::TexturesWeaponry::turret_laser)
{
}

LaserTurret::LaserTurret(Configuration::TexturesWeaponry tex_id)
	: Weapon(tex_id)
{
	
}

void LaserTurret::setPattern(Laser::Patterns pattern)
{
	m_Pattern = pattern;
}

void LaserTurret::createBullet()
{
	auto shot = std::make_unique<Laser>(Configuration::TexturesWeaponry::ammo_laser, Configuration::boundaries, -90, 1200, m_Pattern);
	shot->setPosition(m_Position);
	shot->setRotation(m_Sprite.getRotation());


	m_Shots.push_back(std::move(shot));
}

void LaserTurret::createSound()
{
	auto sound = std::make_unique<sf::Sound>(Configuration::sounds.get(Configuration::Sounds::laser));
	float volume = 100.f * Configuration::m_MasterVolume / 100.f * Configuration::m_SoundEffectsVolume / 100.f;
	sound->setVolume(volume);

	sound->setAttenuation(1.f);
	sound->setPosition(m_Position.x, -m_Position.y, 0.f);
	sound->setMinDistance(std::sqrtf(200.f * 200.f + 300.f * 300.f));

	sound->play();

	m_Sounds.emplace(std::move(sound));
}

void LaserTurret::updateIndividualBehavior(const sf::Time& deltaTime)
{
}
