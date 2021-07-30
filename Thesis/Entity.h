#pragma once
#include "Collision.h"
#include "World.h"
#include "Configuration.h"

class Entity : public sf::Drawable
{
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;

protected:
	sf::Sprite m_Sprite;
	sf::RectangleShape m_Shape;
	double hp;

	sf::Vector2f m_Velocity;

	World& m_World; // world reference to manipulate entities

	bool m_Alive;

public:
	Entity(const Entity&) = delete;
	Entity& operator=(const Entity&) = delete;

	Entity(Configuration::Textures tex_id, World& world);
	virtual ~Entity();

	virtual bool isAlive() const;
	virtual bool isCollide(const Entity& other) const = 0;

	const sf::Vector2f& getPosition() const;
	
	template<typename ... Args>
	void setPosition(Args&& ... args);
	
	virtual void update(sf::Time deltaTime) = 0;
	virtual void onDestroy();
};

