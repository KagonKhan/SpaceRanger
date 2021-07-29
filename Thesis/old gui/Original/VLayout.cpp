#include "VLayout.h"

namespace GUI
{
	GUI::VLayout::VLayout(Widget* parent)
		: Layout(parent)
	{

	}

	GUI::VLayout::~VLayout()
	{
		clear();
	}

	sf::Vector2f GUI::VLayout::getSize() const
	{
		float max_x = 0;
		float y = 0;

		for (Widget* widget : m_Widgets) {
			sf::Vector2f size = widget->getSize();
			if (size.x > max_x)
				max_x = size.x;

			y += m_Space + size.y;
		}
		return sf::Vector2f(max_x + m_Space * 2, y + m_Space);
	}

	void VLayout::clear()
	{
		for (Widget* widget : m_Widgets)
			if (widget->m_Parent == this)
				delete widget;

		m_Widgets.clear();
		updateShape();
	}

	void GUI::VLayout::updateShape()
	{
		float max_x = m_Parent ? m_Parent->getSize().x : 0;

		for (Widget* widget : m_Widgets) 			
			if (widget->getSize().x > max_x)
				max_x = widget->getSize().x;
		
		float pos_y = m_Space;
		if(m_Parent)
			pos_y = (m_Parent->getSize().y - getSize().y ) / 2.0f;

		for (Widget* widget : m_Widgets) {
			sf::Vector2f size = widget->getSize();
			widget->setPosition((max_x - size.x) / 2.0, pos_y);
			pos_y += size.y + m_Space;
		}

		Widget::updateShape();
	}

	bool GUI::VLayout::processEvent(const sf::Event& sfevent, const sf::Vector2f& parent_pos)
	{
		for (Widget* widget : m_Widgets)
			if (widget->processEvent(sfevent, parent_pos))
				return true;

		return false;
	}

	void GUI::VLayout::processEvents(const sf::Vector2f& parent_pos)
	{
		for (Widget* widget : m_Widgets)
			widget->processEvents(parent_pos);
	}

	void GUI::VLayout::add(Widget* widget)
	{
		widget->m_Parent = this;
		m_Widgets.emplace_back(widget);
		updateShape();
	}

	Widget* GUI::VLayout::at(unsigned int index) const
	{
		return m_Widgets.at(index);
	}

	void GUI::VLayout::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		for (Widget* widget : m_Widgets)
			target.draw(*widget, states);
	}
}