#include "pch.h"
#include "Entity.h"

Entity::Entity(Configuration::Textures tex_id)
	: m_Alive(true)
{
	m_Sprite.setTexture(Configuration::textures.get(tex_id));

	/** TO DO **/
	/*
		Load texture from configuration
		set origin
		set position
	
	*/
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
