#include "pch.h"
#include "Player.h"

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_Sprite);
}


Player::Player(Configuration::Textures tex_id, const sf::Vector2f& boundaries)
	: Ship(100, tex_id), ActionTarget(Configuration::playerInputs)
{
	m_Sprite.setTexture(Configuration::textures.get(tex_id));
}

void Player::update(const sf::Time& deltaTime)
{

}
