#include "Widget.h"

namespace GUI
{
	Widget::Widget(Widget* parent)
		: m_Parent(parent)
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


	bool Widget::processEvent(const sf::Event& sfevent, const sf::Vector2f& parent_pos)
	{
		return false;
	}

	void Widget::processEvents(const sf::Vector2f& parent_pos)
	{

	}

	void Widget::updateShape()
	{
		if (m_Parent)
			m_Parent->updateShape();
	}

}