#include "pch.h"
#include "Entity.h"

void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	//target.draw(m_Shape);
	target.draw(m_Sprite);
}

// Entities have centered origins
Entity::Entity(const sf::Texture& texture)
	: m_Sprite(texture), m_IsVisible(true)
{

	sf::Vector2f sprite_size(m_Sprite.getGlobalBounds().width, m_Sprite.getGlobalBounds().height);
	m_Sprite.setOrigin(sprite_size / 2.f);
	m_Shape.setOrigin(sprite_size / 2.f);
	m_Shape.setSize(sprite_size);
}


Entity::~Entity()
{

}


sf::Vector2f Entity::getPosition() const
{
	return m_Position;
}

sf::Vector2f Entity::getSize() const
{
	return sf::Vector2f(m_Sprite.getGlobalBounds().width, m_Sprite.getGlobalBounds().height); 
}

sf::Vector2f Entity::getRectangleSize() const
{
	return m_Shape.getSize();
}

sf::Sprite& Entity::getSprite()
{
	return m_Sprite;
}

void Entity::setPosition(const sf::Vector2f& pos)
{
	m_Position = pos;
	m_Shape.setPosition(pos);
	m_Sprite.setPosition(pos);	
}

void Entity::setPosition(float x, float y)
{
	setPosition(sf::Vector2f(x, y));
}

bool Entity::isVisible()
{
	return m_IsVisible;
}

void Entity::setVisible(bool visibility)
{
	m_IsVisible = visibility;
}
