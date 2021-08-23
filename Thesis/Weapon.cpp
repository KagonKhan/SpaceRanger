#include "pch.h"

#include "Weapon.h"
#include "Entity.h"

void Weapon::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(Configuration::tar);
	for (auto&& shot : m_Shots)
		target.draw(*shot);

	target.draw(m_Sprite);
}

Weapon::Weapon(Configuration::Textures tex_id)
	: Entity(tex_id), m_Target(nullptr), m_FiringRate(0), m_TimeSinceLastShot(0), m_FiringDelay(0), m_IsWeaponActive(false)
{
	Configuration::tar.setSize(sf::Vector2f(50, 50));
	Configuration::tar.setFillColor(sf::Color::Red);
	Configuration::tar.setPosition(300, 300);
}


#pragma region SETTERS / GETTERS
void Weapon::setFiringRate(float rate)
{
	m_FiringRate=rate;
	m_FiringDelay = 1 / m_FiringRate;
}

void Weapon::setTarget(const Entity* target)
{
	m_Target = target;
}

void Weapon::setIsWeaponActive(bool isActive)
{
	m_IsWeaponActive = isActive;
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

void Weapon::setWeaponOffset(const sf::Vector2f& offset)
{
	m_WeaponOffset = offset;
}

const sf::Vector2f& Weapon::getWeaponOffset()
{
	return m_WeaponOffset;
}

void Weapon::setPosition(const sf::Vector2f& pos)
{
	m_Position = pos + m_WeaponOffset;
	m_Shape.setPosition(m_Position);
	m_Sprite.setPosition(m_Position);
}

#pragma endregion


void Weapon::shoot()
{
	if(m_IsWeaponActive)
		if (m_TimeSinceLastShot > m_FiringDelay) {
			createBullet();
			createSound();
			m_TimeSinceLastShot = 0;
		}
}

void Weapon::update(const sf::Time& deltaTime)
{
	updateTimings(deltaTime);

	updateTrackingTarget(deltaTime);

	updateBulletsAndCheckForDeletion(deltaTime);

	deleteFinishedSounds();
}

void Weapon::updateTimings(const sf::Time& deltaTime)
{
	m_TimeSinceLastShot += deltaTime.asSeconds();
}

void Weapon::updateBulletsAndCheckForDeletion(const sf::Time& deltaTime)
{
	for (int i = 0; i < m_Shots.size(); ++i) {
		m_Shots[i]->update(deltaTime);

		if (m_Shots[i]->getShouldBeDeleted())
			m_Shots.erase(m_Shots.begin() + i);

	}
}

void Weapon::updateTrackingTarget(const sf::Time& deltaTime)
{

	sf::Vector2f target_pos = Configuration::tar.getPosition();
	sf::Vector2f weapon_pos = getPosition();
	
	float angle = atan2f(target_pos.y - weapon_pos.y, target_pos.x - weapon_pos.x);
	angle *= 180.f / M_PIl;
	angle -= 90.f;

	m_Sprite.setRotation(angle);


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::I))
		Configuration::tar.move(0, -5);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::L))
		Configuration::tar.move(5, 0);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::K))
		Configuration::tar.move(0, 5);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::J))
		Configuration::tar.move(-5, 0);
}

void Weapon::deleteFinishedSounds()
{
	m_Sounds.remove_if([](const std::unique_ptr<sf::Sound>& sound) -> bool {
		return sound->getStatus() != sf::SoundSource::Status::Playing;
		});
}

/* =============================    Laser Turret    ========================= */

LaserTurret::LaserTurret(Configuration::Textures tex_id)
	: Weapon(tex_id)
{

}

void LaserTurret::createBullet()
{
	std::unique_ptr<Laser> shot(new Laser(Configuration::Textures::Ammo_Laser, Configuration::boundaries, -90, 1200));
	shot->setPosition(m_Position);
	shot->setRotation(m_Sprite.getRotation());


	m_Shots.push_back(std::move(shot));
}

void LaserTurret::createSound()
{
	std::unique_ptr<sf::Sound> sound(new sf::Sound(Configuration::sounds.get(Configuration::Sounds::LaserPlayer)));
	sound->setAttenuation(0);
	sound->setVolume(20);
	sound->play();



	m_Sounds.emplace_back(std::move(sound));
}


/* =============================    Missile Turret    ========================= */

MissileTurret::MissileTurret(Configuration::Textures tex_id)
	: Weapon(tex_id)
{
}

void MissileTurret::createBullet()
{
	std::unique_ptr<Missile> shot(new Missile(Configuration::Textures::Ammo_Rocket, Configuration::boundaries, -90, 400));
	shot->setPosition(m_Position);
	shot->setRotation(m_Sprite.getRotation());

	m_Shots.push_back(std::move(shot));
}

void MissileTurret::createSound()
{
	std::unique_ptr<sf::Sound> sound(new sf::Sound(Configuration::sounds.get(Configuration::Sounds::Missile)));
	sound->setAttenuation(0);
	sound->setVolume(20);
	sound->play();




	m_Sounds.emplace_back(std::move(sound));
}
