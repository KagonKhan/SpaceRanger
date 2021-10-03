#include "pch.h" 
#include "Ship.h"


Ship::Ship(float max_hp, Configuration::TexturesShips tex_id)
	: Entity(Configuration::textures_ships.get(tex_id)), IsLiving(max_hp), m_OnDestroy(*this)
{
	m_Sprite.setScale(0.5f, 0.5f);
}

// CAREFUL: order is strictly enforced, which may lead to bugs
void Ship::update(const sf::Time& deltaTime)
{ 
	// Update weapons even if the entity is not alive, otherwise the shots will just disappear
	updateWeapons(deltaTime);
	 
	if (m_OnDestroy.isMarkedForDeletion())
		updateOnDestroy(deltaTime);
	

	if (m_AreActionsBlocked)		return;


	updateIndividualBehavior(deltaTime);
	updateMovement(deltaTime);
}

void Ship::updateWeapons(const sf::Time& deltaTime)
{
	static const auto area = sf::FloatRect(sf::Vector2f(0, 0), Configuration::boundaries);
	for (auto&& weapon : m_Weapons) {
		weapon->update(deltaTime);
		if (!Helpers::CheckIfPointContainedInArea(m_Position, area))
			weapon->setIsWeaponActive(false);
		else
			weapon->setIsWeaponActive(true);

	}
}

void Ship::updateOnDestroy(const sf::Time& deltaTime)
{
	m_OnDestroy.update(deltaTime);
}


void Ship::repositionSprites(sf::Vector2f positionAt)
{
	m_Position = positionAt;

	m_Sprite.setPosition(m_Position);
	m_Shape.setPosition(m_Position);

	for (auto&& weapon : m_Weapons)
		weapon->setPosition(m_Position);
}




void Ship::setAreActionsBlocked(bool is_blocked)
{
	m_AreActionsBlocked = is_blocked;

	// Freeze movement
	if(is_blocked)
		m_Direction = sf::Vector2f(0, 0);
}

void Ship::setWeaponsAsActive(bool active) const
{
	for (auto&& weapon : m_Weapons)
		weapon->setIsWeaponActive(active);
}




int Ship::getMaxCap(const std::vector<Ammunition*> container) const
{
	static int max_cap = container.size();

	if (static_cast<int>(container.size()) > max_cap) {

		max_cap = container.size();
	}

	return max_cap;
}

std::vector<Ammunition*>& Ship::getAmmoOnScreen()
{

	// TODO: Test if this actually makes a difference
	int max_cap = getMaxCap(ammoOnScreen);
	ammoOnScreen.clear();
	ammoOnScreen.reserve(max_cap);


	for (auto&& weapon : m_Weapons)
		for (auto&& ammo : weapon->getAmmoOnScreen()) 
			ammoOnScreen.push_back(ammo);

	return ammoOnScreen;
}

