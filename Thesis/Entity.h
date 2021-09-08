#pragma once
#include "Collision.h"
#include "Configuration.h"

class Entity : 
	public sf::Drawable
{
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates) const;

protected:
	sf::Sprite m_Sprite;
	sf::RectangleShape m_Shape; // Possibly for collision detection

	bool m_IsVisible;

	sf::Vector2f m_Position, m_Velocity, m_Direction;

public:
	Entity(const sf::Texture& texture);
	virtual ~Entity();

	typedef std::unique_ptr<Entity> ptr;

	sf::Vector2f getPosition() const;
	sf::Vector2f getSize() const;
	sf::Vector2f getRectangleSize() const;
	sf::Sprite& getSprite();

	virtual void setPosition(const sf::Vector2f& pos);
	virtual void setPosition(float x, float y);
	virtual void update(const sf::Time& deltaTime) = 0;

	bool isVisible();
	void setVisible(bool visibility);
};

