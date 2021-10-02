#include "pch.h" 
#include "Ship.h"

void Ship::draw(sf::RenderTarget& target, sf::RenderStates) const
{
	target.draw(m_Sprite);

	for (auto&& weapon : m_Weapons)
		target.draw(*weapon);

}


Ship::Ship(float max_hp, Configuration::TexturesShips tex_id)
	: Entity(Configuration::textures_ships.get(tex_id)), IsLiving(max_hp)
{}

// CAREFUL: order is strictly enforced, which may lead to bugs
void Ship::update(const sf::Time& deltaTime)
{ 
	// Update weapons even if the entity is not alive, otherwise the shots will just disappear
	updateWeapons(deltaTime);
	updateCanBeDeleted();


	if (!isAlive()) {
		m_AreActionsBlocked = true;
		return;
	}

	//if (m_AreActionsBlocked)		return;


	updateIndividualBehavior(deltaTime);
	updateMovement(deltaTime);
}

void Ship::updateWeapons(const sf::Time& deltaTime)
{
	for (auto&& weapon : m_Weapons)
		weapon->update(deltaTime);
}

// Maybe there is no point in checking every frame if can be deleted, and just when it tries to be deleted
void Ship::updateCanBeDeleted()
{
	if (ammoOnScreen.empty())
		m_CanBeDeleted = true;
	else
		m_CanBeDeleted = false;
}

void Ship::repositionSprites()
{
	m_Sprite.setPosition(m_Position);
	m_Shape.setPosition(m_Position);

	for (auto&& weapon : m_Weapons)
		weapon->setPosition(m_Position);
}



#pragma region SETTERS / GETTERS

void Ship::setPosition(const sf::Vector2f& pos)
{
	m_Position = pos;
	repositionSprites(); 
}

void Ship::move(const sf::Vector2f& moveBy)
{
	m_Position += moveBy;
	repositionSprites();
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

	if (container.size() > max_cap) {
		BOOST_LOG_TRIVIAL(info) << max_cap << " : " << container.size();

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

#pragma endregion





void Ship::markForDeletion()
{
	m_MarkedForDeletion = true;
	m_AreActionsBlocked = true;
}

void Ship::onDestroy()
{
	setPosition(-9.f, -9.f);
	markForDeletion();
}
