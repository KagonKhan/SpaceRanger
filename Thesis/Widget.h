#pragma once
#include "Configuration.h"

/* Base class for polymorphism*/
class Widget : public sf::Drawable
{
protected:
	friend class UI;
	friend class VerticalLayout;
	friend class HorizontalLayout;
	friend class VerticalScrollingLayout;

	sf::Vector2f m_Position;

	virtual void processEvent(const sf::Event& sfevent);

public:
	Widget(const Widget&) = delete; 
	Widget& operator=(const Widget&) = delete;

	Widget(Widget* parent = nullptr);
	virtual ~Widget();



	virtual void setPosition(const sf::Vector2f& pos);
	virtual void setPosition(float x, float y);

	virtual sf::Vector2f getSize() const = 0;
	virtual const sf::Vector2f& getPosition() const;



	virtual void update(const sf::Time& deltaTime);
}; 