#pragma once
#include "Collision.h"
#include "Configuration.h"

class Entity : public sf::Drawable
{
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;

protected:
	sf::Sprite m_Sprite;
	sf::RectangleShape m_Shape; // Possibly for collision detectio


	sf::Vector2f m_Position, m_Velocity, m_Direction;

	bool m_Alive;

public:
	Entity(const Entity&) = delete;
	Entity& operator=(const Entity&) = delete;

	Entity(Configuration::Textures tex_id);
	virtual ~Entity();

	virtual bool isAlive() const;
	virtual bool isCollide(const Entity& other) const = 0;

	const sf::Vector2f& getPosition() const;
	
	template<typename ... Args>
	void setPosition(Args&& ... args);
	
	virtual void update(sf::Time deltaTime) = 0;
	virtual void onDestroy();
};

class Ship :
	public Entity
{
	double hp;

public:


};


class Weapon :
	public Entity
{


};

class Ammunition :
	public Entity
{

};