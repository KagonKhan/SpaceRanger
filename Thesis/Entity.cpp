#include "pch.h"
#include "Entity.h"

Entity::Entity(Configuration::Textures tex_id)
	: m_Alive(true)
{
	m_Sprite.setTexture(Configuration::textures.get(tex_id));

	sf::Vector2f sprite_size(m_Sprite.getGlobalBounds().width, m_Sprite.getGlobalBounds().height);

	m_Sprite.setOrigin(sprite_size / 2.f);

	m_Shape.setOrigin(sprite_size / 2.f);
	m_Shape.setSize(sprite_size);


}


Entity::~Entity()
{

}

void Entity::onDestroy()
{
	m_Alive = false;
}

bool Entity::isAlive() const
{
	return m_Alive;
}

const sf::Vector2f& Entity::getPosition() const
{
	return m_Position;
}

const sf::Vector2f& Entity::getSize() const
{
	return sf::Vector2f(m_Sprite.getGlobalBounds().width, m_Sprite.getGlobalBounds().height);
}

const sf::Vector2f& Entity::getRectangleSize() const
{
	return m_Shape.getSize();
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
