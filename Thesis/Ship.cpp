#include "pch.h" 
#include "Ship.h"


void Ship::draw(sf::RenderTarget& target, sf::RenderStates) const
{
	for (auto&& weapon : m_Weapons)
		target.draw(*weapon);


	target.draw(m_Sprite);
}

Ship::Ship(double max_hp, Configuration::TexturesShips tex_id)
	: Entity(Configuration::textures_ships.get(tex_id)), IsLiving(max_hp), HasWeapons(), CanCollide()
{

}

Ship::~Ship()
{
}

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


void Ship::initWeapon(const sf::Vector2f& offset, float firing_rate, WeaponType weapon_type, float rotation)
{
	switch (weapon_type) {
		case WeaponType::Laser: {
			std::unique_ptr<LaserTurret> weapon(new LaserTurret(Configuration::TexturesWeaponry::turret_laser));
			addWeapon(std::move(weapon));

			break;
		}
		case WeaponType::Missile: {
			std::unique_ptr<MissileTurret> weapon(new MissileTurret(Configuration::TexturesWeaponry::turret_laser));
			addWeapon(std::move(weapon));

			break;
		}
		case WeaponType::Beam: {
			std::unique_ptr<BeamTurret> weapon(new BeamTurret(Configuration::TexturesWeaponry::turret_laser, *this));
			addWeapon(std::move(weapon));

			break;
		}
	}



	m_Weapons.back()->setPosition(m_Position);
	m_Weapons.back()->setWeaponOffset(offset);
	m_Weapons.back()->setFiringRate(firing_rate);
	m_Weapons.back()->setSpriteRotation(rotation);
	m_Weapons.back()->setIsWeaponActive(true);
}