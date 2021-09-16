#include "pch.h" 
#include "Ship.h"

void Ship::draw(sf::RenderTarget& target, sf::RenderStates) const
{
	target.draw(m_Sprite);


	for (auto&& weapon : m_Weapons)
		target.draw(*weapon);


}

Ship::Ship(double max_hp, Configuration::TexturesShips tex_id)
	: Entity(Configuration::textures_ships.get(tex_id)), IsLiving(max_hp), HasWeapons(), CanCollide(),
	m_AreActionsBlocked(false), m_CanBeDeleted(false), m_MarkedForDeletion(false)
{}

Ship::~Ship(){}

void Ship::update(const sf::Time& deltaTime)
{ 
	// Update weapons even if the entity is not alive, otherwise the shots will just disappear
	updateWeapons(deltaTime);


	if (!isAlive()) {
		m_AreActionsBlocked = true;
		return;
	}
	if (m_AreActionsBlocked)
		return;



	updateIndividualBehavior(deltaTime);
	updateMovement(deltaTime);
	updatePosition(deltaTime);
	updateSprites(deltaTime);
	
}

void Ship::updateMovement(const sf::Time& deltaTime){}

void Ship::updatePosition(const sf::Time& deltaTime)
{
	m_Sprite.setPosition(m_Position);
	m_Shape.setPosition(m_Position);

	for (auto&& weapon : m_Weapons)
		weapon->setPosition(m_Position);
}

void Ship::updateSprites(const sf::Time& deltaTime){}

void Ship::updateWeapons(const sf::Time& deltaTime)
{
	for (auto&& weapon : m_Weapons)
		weapon->update(deltaTime);
}

#pragma region SETTERS / GETTERS

void Ship::setPosition(const sf::Vector2f& pos)
{
	m_Position = pos;
	m_Shape.setPosition(m_Position);
	m_Sprite.setPosition(m_Position);

	for (auto&& weapon : m_Weapons)
		weapon->setPosition(m_Position);
}

void Ship::setPosition(float x, float y)
{
	setPosition(sf::Vector2f(x, y));
}

void Ship::setAreActionsBlocked(bool is_blocked)
{
	m_AreActionsBlocked = is_blocked;

	// Freeze movement
	m_Direction = sf::Vector2f(0, 0);
}

bool Ship::getAreActionsBlocked() const
{
	return m_AreActionsBlocked;
}

std::vector<Ammunition*>& Ship::getShots()
{
	ghostPTR.clear();
	for (auto&& weapon : m_Weapons)
		for (auto&& ammo : weapon->getShots()) 
			ghostPTR.push_back(ammo);

	if (ghostPTR.size() == 0)
		m_CanBeDeleted = true;
	else
		m_CanBeDeleted = false;

	return ghostPTR;
}

bool Ship::canBeDeleted()
{
	return m_CanBeDeleted;
}

bool Ship::shouldBeDeleted()
{
	return m_MarkedForDeletion;
}

void Ship::markForDeletion()
{
	m_MarkedForDeletion = true;
	m_AreActionsBlocked = true;
}

#pragma endregion

void Ship::onDestroy()
{
	setPosition(-99999, -99999);
	markForDeletion();
}

