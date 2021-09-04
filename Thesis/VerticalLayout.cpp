#include "pch.h"
#include "VerticalLayout.h"

VerticalLayout::VerticalLayout(opt_ref parent, float padding)
	: Layout(parent, padding)
{
	puts("Vertical layout\tctor");
}

VerticalLayout::~VerticalLayout()
{
	puts("Vertical layout\tdtor");
}


void VerticalLayout::updateShape()
{
	sf::Vector2f pos(m_Position);

	for (auto&& widget : m_Widgets) {
		widget->setPosition(pos);

		pos.y += widget->getSize().y + m_Padding;
	}
}


void VerticalLayout::update(const sf::Time&)
{
}


sf::Vector2f VerticalLayout::getSize() const
{
	float max_x{};
	float y{};

	for (auto&& widget : m_Widgets) {
		const sf::Vector2f curr_widget_size(widget->getSize());
		y += curr_widget_size.y + m_Padding;

		if (max_x < curr_widget_size.x)
			max_x = curr_widget_size.x;

	}
	return sf::Vector2f(max_x, y - m_Padding);
}
