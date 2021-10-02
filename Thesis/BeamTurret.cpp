#include "pch.h"
#include "BeamTurret.h"
#include "Beam.h"
#include "PlayerShip.h"
BeamTurret::BeamTurret(Entity::opt_ref parent)
	:BeamTurret(Configuration::TexturesWeaponry::turret_laser, parent)
{
}
BeamTurret::BeamTurret(Configuration::TexturesWeaponry tex_id, Entity::opt_ref parent)
	: Weapon(tex_id), m_Parent(parent)
{

}

void BeamTurret::stop()
{
	m_Shots.clear();
}

void BeamTurret::createBullet()
{
	auto shot = std::make_unique<Beam>(Configuration::TexturesWeaponry::ammo_beam, Configuration::boundaries, -90, 400);
	shot->setPosition(m_Position);
	shot->setRotation(m_Sprite.getRotation());

	m_Shots.push_back(std::move(shot));

	if (m_Parent.has_value())
		if (PlayerShip* player = dynamic_cast<PlayerShip*>(&m_Parent.value().get()); player != nullptr)
			player->setAreActionsBlocked(true);
}

void BeamTurret::createSound()
{
	auto sound = std::make_unique<sf::Sound>(Configuration::sounds.get(Configuration::Sounds::beam));
	float volume = 100.f * Configuration::m_MasterVolume / 100.f * Configuration::m_SoundEffectsVolume / 100.f;

	sound->setAttenuation(1.f);
	sound->setPosition(m_Position.x, -m_Position.y, 0.f);
	sound->setMinDistance(std::sqrtf(200.f * 200.f + 300.f * 300.f));
	sound->setVolume(volume * 10);
	sound->play();

	m_Sounds.emplace(std::move(sound));
}

void BeamTurret::updateIndividualBehavior(const sf::Time& deltaTime)
{
	if (m_Parent.has_value() && m_Shots.empty())
		if (auto&& parent = m_Parent.value().get(); typeid(parent).name() == typeid(PlayerShip).name())
			dynamic_cast<PlayerShip*>(&m_Parent.value().get())->setAreActionsBlocked(false);
		
}
