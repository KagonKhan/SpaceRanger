#pragma once
#include "Collision.h"
#include "Configuration.h"

class Entity : public sf::Drawable
{
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;

protected:
	sf::Sprite m_Sprite;
	sf::RectangleShape m_Shape; // Possibly for collision detection


	sf::Vector2f m_Position, m_Velocity, m_Direction;

	bool m_Alive;

public:
	Entity(const Entity&) = delete;
	Entity& operator=(const Entity&) = delete;

	Entity(const sf::Texture& texture);
	virtual ~Entity();

	virtual bool isAlive() const;


	sf::Vector2f getPosition() const;
	sf::Vector2f getSize() const;
	sf::Vector2f getRectangleSize() const;

	virtual void setPosition(const sf::Vector2f& pos);
	virtual void setPosition(float x, float y);
	virtual void update(const sf::Time& deltaTime) = 0;
	virtual void onDestroy();
};

