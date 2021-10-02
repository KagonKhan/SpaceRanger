#include "pch.h"
#include "Entity.h"

// Entities have centered origins
Entity::Entity(const sf::Texture& texture)
	: m_Sprite(texture)
{
	setOrigins();
}


void Entity::setOrigins()
{
	sf::Vector2f sprite_size(getSize());

	m_Sprite.setOrigin	(sprite_size / 2.f);
	m_Shape.setOrigin	(sprite_size / 2.f);
	m_Shape.setSize		(sprite_size / 2.f);
}


void Entity::setPosition(const sf::Vector2f& pos)
{
	m_Position = pos + m_Offset;
	m_Shape.setPosition(pos);
	m_Sprite.setPosition(pos);	
}

