#include "pch.h"
#include "BeamTurret.h"
#include "Beam.h"
#include "PlayerShip.h"
BeamTurret::BeamTurret(Configuration::TexturesWeaponry tex_id, Entity::opt_ref parent)
	: Weapon(tex_id), m_Parent(parent)
{

}

BeamTurret::~BeamTurret()
{
}

void BeamTurret::createBullet()
{
	std::unique_ptr<Beam> shot(new Beam(Configuration::TexturesWeaponry::ammo_beam, Configuration::boundaries, -90, 400));
	shot->setPosition(m_Position);
	shot->setRotation(m_Sprite.getRotation());

	m_Shots.push_back(std::move(shot));

	if (typeid(m_Parent).name() == typeid(PlayerShip).name())
		dynamic_cast<PlayerShip*>(&m_Parent.value().get())->setAreActionsBlocked(true);


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
	m_Sounds.emplace_back(std::move(sound));
}

void BeamTurret::updateIndividualBehavior(const sf::Time& deltaTime)
{
	if (m_Shots.empty())
		if(m_Parent.has_value())
		if (typeid(m_Parent.value().get()).name() == typeid(PlayerShip).name()) {
			PlayerShip* ship = dynamic_cast<PlayerShip*>(&m_Parent.value().get());
			if (ship->getAreActionsBlocked())
				ship->setAreActionsBlocked(false);
		}
}