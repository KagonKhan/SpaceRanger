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
	sf::Vector2f m_Position, m_Offset, m_Velocity, m_Direction;

	bool m_IsVisible;

public:
	Entity(const sf::Texture& texture);
	virtual ~Entity();

	virtual void update(const sf::Time& deltaTime) = 0;

#pragma region SETTERS / GETTERS
	typedef std::unique_ptr<Entity> ptr;
	typedef std::optional<std::reference_wrapper<Entity>> opt_ref;
	sf::Vector2f getPosition() const;
	sf::Vector2f getSize() const;
	sf::Vector2f getRectangleSize() const;
	sf::Sprite& getSprite();
	virtual void setPosition(const sf::Vector2f& pos);
	virtual void setPosition(float x, float y);
	void setOffset(float x, float y);
	void setOffset(const sf::Vector2f& offset);
#pragma endregion


	bool isVisible();
	void setVisible(bool visibility);

};

