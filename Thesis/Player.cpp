#include "pch.h"
#include "Player.h"

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_Avatar);
}

Player::Player(Configuration::TexturesPlayer avatar, const sf::Vector2f& boundaries)
	: m_Avatar(Configuration::textures_player.get(avatar)),
	m_Ship(Configuration::TexturesShips::player_ship, boundaries, *this),
	m_PlayerStats({ 100, 1, 0, 0, 100,      0,0,0,0})
{

}

Player::~Player()
{
}

void Player::setPosition(const sf::Vector2f& pos)
{
	m_Position = pos;
	m_Avatar.setPosition(pos);
}

PlayerShip& Player::getPlayerShip() const
{
	return m_Ship;
}

const sf::Sprite& Player::getPlayerShipSprite() const
{
	return m_Ship.getSprite();
}

sf::Vector2f Player::getSpriteSize() const
{
	return { m_Avatar.getGlobalBounds().width, m_Avatar.getGlobalBounds().height };

}

void Player::setSpriteScale(const sf::Vector2f& scale)
{
	m_Avatar.setScale(scale);
}

Player::Stats& Player::getPlayerStats()
{
	return m_PlayerStats;
}
