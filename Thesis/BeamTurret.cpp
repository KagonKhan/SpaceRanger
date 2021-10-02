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
	std::unique_ptr<Beam> shot(new Beam(Configuration::TexturesWeaponry::ammo_beam, Configuration::boundaries, -90, 400));
	shot->setPosition(m_Position);
	shot->setRotation(m_Sprite.getRotation());

	m_Shots.push_back(std::move(shot));

	if (m_Parent.has_value())
		if (PlayerShip* player = dynamic_cast<PlayerShip*>(&m_Parent.value().get()); player != nullptr)
			player->setAreActionsBlocked(true);
}

void BeamTurret::createSound()
{
	std::unique_ptr<sf::Sound> sound(new sf::Sound(Configuration::sounds.get(Configuration::Sounds::beam)));
	float volume = 100.f * Configuration::m_MasterVolume / 100.f * Configuration::m_SoundEffectsVolume / 100.f;

	sound->setAttenuation(1.f);
	sound->setPosition(m_Position.x, -m_Position.y, 0.f);
	sound->setMinDistance(std::sqrt(200 * 200 + 300 * 300));
	sound->setVolume(volume * 10);
	sound->play();

	m_Sounds.emplace(std::move(sound));
}

void BeamTurret::updateIndividualBehavior(const sf::Time& deltaTime)
{
	if (m_Parent.has_value() && m_Shots.empty())
		if (typeid(m_Parent.value().get()).name() == typeid(PlayerShip).name())
			dynamic_cast<PlayerShip*>(&m_Parent.value().get())->setAreActionsBlocked(false);
		
}
