#include "pch.h"
#include "Weapon.h"


void Weapon::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (auto&& shot : m_Shots)
		target.draw(*shot);

	if(m_IsVisible)
		target.draw(m_Sprite);
}

Weapon::Weapon(Configuration::TexturesWeaponry tex_id)
	: Entity(Configuration::textures_weaponry.get(tex_id))
{

}


void Weapon::setFiringRate(float rate)
{
	m_FiringRate=rate;
	m_FiringDelay = 1 / m_FiringRate;
}

void Weapon::shoot(bool makeSound)
{
	if(m_IsWeaponActive && m_TimeSinceLastShot > m_FiringDelay) {
		createBullet();
		if (makeSound) createSound();

		m_TimeSinceLastShot = 0;

	}
}

void Weapon::update(const sf::Time& deltaTime)
{
	updateTimings(deltaTime);
	
	if(m_Target)
		updateTrackingTarget(deltaTime);

	updateBulletsAndCheckForDeletion(deltaTime);

	updateIndividualBehavior(deltaTime);

	deleteFinishedSounds();
}



void Weapon::updateBulletsAndCheckForDeletion(const sf::Time& deltaTime)
{
	for (unsigned int i = 0; i < m_Shots.size(); ++i) {
		m_Shots[i]->update(deltaTime);

		if (m_Shots[i]->canBeDeleted()) {
			m_Shots.erase(m_Shots.begin() + i);
			--i;
		}
	}
}


void Weapon::updateTrackingTarget(const sf::Time&)
{
	sf::Vector2f target_pos = m_Target->getPosition();
	sf::Vector2f weapon_pos = getPosition();
	
	float angle = atan2f(target_pos.y - weapon_pos.y, target_pos.x - weapon_pos.x);
	angle *= 180.f / static_cast<float>(M_PIl);
	angle -= 90.f;

	m_Sprite.setRotation(angle);
}

void Weapon::deleteFinishedSounds()
{
	while (!m_Sounds.empty() && m_Sounds.front()->getStatus() == sf::Sound::Status::Stopped)
		m_Sounds.pop();

	/*m_Sounds.remove_if([](const std::unique_ptr<sf::Sound>& sound) -> bool {
		return sound->getStatus() != sf::SoundSource::Status::Playing;
		});*/
}

std::vector<Ammunition*>& Weapon::getAmmoOnScreen()
{
	ammoOnScreen.clear();

	for (auto&& ammo : m_Shots)
		ammoOnScreen.push_back(ammo.get());

	return ammoOnScreen;
}