#include "pch.h"
#include "Widget.h"

void Widget::processEvent(const sf::Event& sfevent)
{
	
}

Widget::Widget(Widget* parent)
{
}


Widget::~Widget()
{
}

void Widget::setPosition(const sf::Vector2f& pos)
{
	m_Position = pos;
}

void Widget::setPosition(float x, float y)
{
	m_Position = sf::Vector2f(x, y);
}

const sf::Vector2f& Widget::getPosition() const
{
	return m_Position;
}

void Widget::update(const sf::Time& deltaTime)
{
}
