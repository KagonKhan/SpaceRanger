#include "pch.h"
#include "TableLayout.h"

TableLayout::TableLayout(opt_ref parent, float padding, const sf::FloatRect& boundaries)
	: Layout(parent, padding), m_Boundaries(boundaries)
{
	puts("TableLayout\tctor");
	m_Position = sf::Vector2f(boundaries.left, boundaries.top);
}

TableLayout::~TableLayout()
{
	puts("TableLayout\tdtor");
}


void TableLayout::updateShape()
{
	sf::Vector2f pos(m_Position);

	for (auto&& widget : m_Widgets) {
		widget->setPosition(pos);

		const sf::Vector2f size(widget->getSize());

		if (pos.x + size.x + m_Padding <= m_Boundaries.width) {
			pos.x += size.x + m_Padding;
		}
		else {
			pos.x = m_Position.x;
			pos.y += size.y + m_Padding;
		}
	}
}


void TableLayout::update(const sf::Time&)
{
}


sf::Vector2f TableLayout::getSize() const
{
	float max_x{};
	float max_y{};

	for (auto&& widget : m_Widgets) {
		const sf::Vector2f curr_widget_size(widget->getSize());
		const sf::Vector2f curr_widget_pos(widget->getPosition());

		if (max_x < curr_widget_pos.x + curr_widget_size.x)
			max_x = curr_widget_pos.x + curr_widget_size.x;

		if (max_y < curr_widget_pos.y + curr_widget_size.y)
			max_y = curr_widget_pos.y + curr_widget_size.y;
	}
	return sf::Vector2f(max_x - m_Position.x, max_y - m_Position.y);
}
