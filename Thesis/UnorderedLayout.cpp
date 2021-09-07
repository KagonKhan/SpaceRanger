#include "pch.h"
#include "UnorderedLayout.h"

UnorderedLayout::UnorderedLayout(opt_ref parent)
	: Layout(parent, 0.f)
{
	puts("UnorderedLayout\tctor");
}

UnorderedLayout::~UnorderedLayout()
{
	puts("UnorderedLayout\tdtor");
}


void UnorderedLayout::updateShape()
{
	float min_x{ std::numeric_limits<float>::max() };
	float min_y{ std::numeric_limits<float>::max() };

	for (auto&& widget : m_Widgets) {
		const sf::Vector2f curr_widget_pos(widget->getPosition());

		if (min_x > curr_widget_pos.x)	min_x = curr_widget_pos.x;
		if (min_y > curr_widget_pos.y)	min_y = curr_widget_pos.y;
	}

	m_Position = sf::Vector2f(min_x, min_y);
}

void UnorderedLayout::update(const sf::Time&)
{


}

sf::Vector2f UnorderedLayout::getSize() const
{
	float max_x{}, min_x{ std::numeric_limits<float>::max() };
	float max_y{}, min_y{ std::numeric_limits<float>::max() };

	for (auto&& widget : m_Widgets) {
		const sf::Vector2f curr_widget_size(widget->getSize());
		const sf::Vector2f curr_widget_pos(widget->getPosition());

		if (max_x < curr_widget_pos.x + curr_widget_size.x) max_x = curr_widget_pos.x + curr_widget_size.x;
		if (max_y < curr_widget_pos.y + curr_widget_size.y)	max_y = curr_widget_pos.y + curr_widget_size.y;

		if (min_x > curr_widget_pos.x)	min_x = curr_widget_pos.x;
		if (min_y > curr_widget_pos.y)	min_y = curr_widget_pos.y;
	}

	return sf::Vector2f(max_x - min_x, max_y - min_y);
}
