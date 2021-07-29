#include "HLayout.h"

namespace GUI
{
	HLayout::HLayout(Widget* parent)
		: Layout(parent)
	{
	}

	HLayout::~HLayout()
	{
		clear();
	}

	void HLayout::add(Widget* widget)
	{
		widget->m_Parent = this;
		m_Widgets.emplace_back(widget);
		updateShape();
	}

	Widget* HLayout::at(unsigned int index) const
	{
		return m_Widgets.at(index);
	}

	sf::Vector2f HLayout::getSize() const
	{
		float max_y = 0;
		float x = 0;

		for (Widget* widget : m_Widgets)
			if (widget->isVisible()) {
				sf::Vector2f size = widget->getSize();
				if (size.y > max_y)
					max_y = size.y;
				x += m_Space + size.x;
			}

		return sf::Vector2f(x+m_Space, max_y +m_Space * 2);
	}

	void HLayout::clear()
	{
		for (Widget* widget : m_Widgets)
			if (widget->m_Parent == this)
				delete widget;

		m_Widgets.clear();
		updateShape();
	}

	bool HLayout::processEvent(const sf::Event& sfevent, const sf::Vector2f& parent_pos)
	{
		if (m_IsVisible)
			for (Widget* widget : m_Widgets)
				if (widget->isVisible() && widget->processEvent(sfevent, parent_pos))
					return true;

		return false;
	}

	void HLayout::processEvents(const sf::Vector2f& parent_pos)
	{
		if (m_IsVisible)
			for (Widget* widget : m_Widgets)
				if (widget->isVisible())
					widget->processEvents(parent_pos);
	}

	void HLayout::updateShape()
	{
		float max_y = m_Parent ? m_Parent->getSize().y : 0;

		for(Widget* widget: m_Widgets)
			if (widget->isVisible()) {
				sf::Vector2f size = widget->getSize();
				float widget_y = size.y;

				if (widget_y > max_y)
					max_y = widget_y;
			}

		float pos_x = m_Space;
		if(m_Parent)
			pos_x = (m_Parent->getSize().x - getSize().x) / 2.f;

		for(Widget* widget : m_Widgets)
			if (widget->isVisible()) {
				sf::Vector2f size = widget->getSize();
				widget->setPosition(pos_x, (max_y - size.y) / 2.0);
			}

		Widget::updateShape();
	}

	void HLayout::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		if (m_IsVisible)
			for (Widget* widget : m_Widgets)
				if (widget->isVisible())
					target.draw(*widget, states);

	}
}