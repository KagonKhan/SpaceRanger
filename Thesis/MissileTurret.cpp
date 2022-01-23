#include "pch.h"
#include "MissileTurret.h"
#include "Missile.h"

MissileTurret::MissileTurret()
	: MissileTurret(Configuration::TexturesWeaponry::turret_laser)
{
}

MissileTurret::MissileTurret(Configuration::TexturesWeaponry tex_id)
	: Weapon(tex_id)
{
}

MissileTurret::~MissileTurret()
{
}


void MissileTurret::createBullet()
{
	auto shot = std::make_unique<Missile>(Configuration::TexturesWeaponry::ammo_missile, Configuration::TexturesWeaponry::ammo_missile_thrusters, Configuration::boundaries, -90, 400);
	shot->setPosition(m_Position);
	shot->setRotation(m_Sprite.getRotation());

	if (m_Target)
		shot->lockOnTarget(m_Target);

	m_Shots.push_back(std::move(shot));
}

void MissileTurret::createSound()
{
	auto sound = std::make_unique<sf::Sound>(Configuration::sounds.get(Configuration::Sounds::missile));
	float volume = 100.f * Configuration::m_MasterVolume / 100.f * Configuration::m_SoundEffectsVolume / 100.f;
	sound->setVolume(volume);


	sound->setAttenuation(8.f);
	sound->setPosition(m_Position.x, -m_Position.y, 0.f);
	sound->setMinDistance(std::sqrt(200 * 200 + 300 * 300));

	sound->play();
	m_Sounds.emplace(std::move(sound));
}

void MissileTurret::updateIndividualBehavior(const sf::Time& deltaTime)
{
}
