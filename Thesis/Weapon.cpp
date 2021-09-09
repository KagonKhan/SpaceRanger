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
	: Entity(Configuration::textures_weaponry.get(tex_id)),
	m_Target(nullptr), m_FiringRate(0), m_TimeSinceLastShot(0), m_FiringDelay(0), m_IsWeaponActive(false)
{

}

Weapon::~Weapon()
{
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

bool Weapon::isActive()
{
	return m_IsWeaponActive;
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

void Weapon::setPosition(float x, float y)
{
	setPosition(sf::Vector2f(x, y));
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
	
	if(m_Target)
		updateTrackingTarget(deltaTime);

	updateBulletsAndCheckForDeletion(deltaTime);

	updateIndividualBehavior(deltaTime);

	deleteFinishedSounds();
}


void Weapon::updateTimings(const sf::Time& deltaTime)
{
	m_TimeSinceLastShot += deltaTime.asSeconds();
}

void Weapon::updateBulletsAndCheckForDeletion(const sf::Time& deltaTime)
{
	for (unsigned int i = 0; i < m_Shots.size(); ++i) {
		m_Shots[i]->update(deltaTime);

		if (m_Shots[i]->canBeDeleted())
			m_Shots.erase(m_Shots.begin() + i);

	}
}

void Weapon::updateTrackingTarget(const sf::Time& deltaTime)
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
	m_Sounds.remove_if([](const std::unique_ptr<sf::Sound>& sound) -> bool {
		return sound->getStatus() != sf::SoundSource::Status::Playing;
		});
}

std::vector<Ammunition*>& Weapon::getShots()
{
	ghostPTR.clear();

	for (auto&& ammo : m_Shots)
		ghostPTR.push_back(ammo.get());

	return ghostPTR;
}