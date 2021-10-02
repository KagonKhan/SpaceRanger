#pragma once
#include "Collision.h"
#include "Configuration.h"

class Entity : 
	public sf::Drawable
{
protected:
	sf::Sprite					m_Sprite;
	sf::RectangleShape			m_Shape;		 // Possibly for collision detection

	sf::Vector2f				m_Position;
	sf::Vector2f				m_Offset;

	sf::Vector2f				m_Direction;
	float						m_Speed;

	bool						m_IsVisible{ true };


	void setOrigins();

public:
	explicit Entity(const sf::Texture& texture);


	virtual void update(const sf::Time& deltaTime) = 0;


	using ptr		= std::unique_ptr<Entity>;
	using opt_ref	= std::optional<std::reference_wrapper<Entity>>;


	virtual void setPosition(const sf::Vector2f& pos);
	virtual void setPosition(float x, float y)					{			setPosition(sf::Vector2f(x, y));					}
	void setOffset(const sf::Vector2f& offset)					{			m_Offset = offset;									}
	void setOffset(float x, float y)							{			m_Offset = sf::Vector2(x, y);						}
	void setVisible(bool visibility)							{			m_IsVisible = visibility;							}
	bool isVisible() const										{			return m_IsVisible;									}
	sf::Sprite& getSprite()										{			return m_Sprite;									}
	sf::Vector2f getPosition() const							{			return m_Position + m_Offset;						}
	[[maybe_unused]]sf::Vector2f getRectangleSize() const		{			return m_Shape.getSize();							}
	sf::FloatRect getRect() const								{			return m_Sprite.getGlobalBounds();					}
	sf::Vector2f getSize() const								{			return { getRect().width, getRect().height };		}
};

