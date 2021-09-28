#include "pch.h"
#include "Player.h"

void Player::draw(sf::RenderTarget& target, sf::RenderStates) const
{
	target.draw(m_Avatar);
}

Player::Player(Configuration::TexturesPlayer avatar, const sf::Vector2f& boundaries)
	: m_Avatar(Configuration::textures_player.get(avatar)),
	m_Ship(Configuration::TexturesShips::player_ship, boundaries, *this)
{

}


void Player::setPosition(const sf::Vector2f& pos)
{
	m_Position = pos;
	m_Avatar.setPosition(pos);
}
