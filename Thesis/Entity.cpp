#include "pch.h"
#include "Entity.h"

template<typename ... Args>
inline void Entity::setPosition(Args&& ... args)
{
	m_Sprite.setPosition(std::forward<Args>(args)...);
	m_Shape.setPosition(std::forward<Args>(args)...);
}

Entity::Entity(Configuration::Textures tex_id, World& world)
	: m_World(world), m_Alive(true)
{
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
	return m_Sprite.getPosition();
}
