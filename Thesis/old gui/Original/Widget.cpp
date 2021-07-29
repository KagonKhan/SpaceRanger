#include "Widget.h"

namespace GUI
{
	Widget::Widget(Widget* parent)
		: m_Parent(parent), m_IsVisible(true)
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

	void Widget::hide()
	{
		if (m_IsVisible == true)
		{
			m_IsVisible = false;
			updateShape();
		}

	}

	bool Widget::isHidden() const
	{
		return !m_IsVisible;
	}

	void Widget::show()
	{
		if (m_IsVisible == false)
		{
			m_IsVisible = true;
			updateShape();
		}

	}

	bool Widget::isVisible() const
	{
		return m_IsVisible;
	}

	void Widget::toggle()
	{
		m_IsVisible = !m_IsVisible;
		updateShape();
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