#include "pch.h"
#include "HorizontalLayout.h"

HorizontalLayout::HorizontalLayout(opt_ref parent, float padding)
	: Layout(parent, padding)
{

}

HorizontalLayout::~HorizontalLayout()
{

}


void HorizontalLayout::updateShape()
{
	sf::Vector2f pos(m_Position);

	for (auto&& widget : m_Widgets) {
		widget->setPosition(pos);

		pos.x += widget->getSize().x + m_Padding;
	}
}


void HorizontalLayout::update(const sf::Time&)
{
}


sf::Vector2f HorizontalLayout::getSize() const
{
	float max_y{};
	float x{};

	for (auto&& widget : m_Widgets) {
		const sf::Vector2f curr_widget_size(widget->getSize());
		x += curr_widget_size.x + m_Padding;

		if (max_y < curr_widget_size.y)
			max_y = curr_widget_size.y;
	}

	return sf::Vector2f(x - m_Padding, max_y);
}
