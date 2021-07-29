#include "Widget.h"

bool Widget::processEvent(const sf::Event& sfevent)
{
	return false;
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
