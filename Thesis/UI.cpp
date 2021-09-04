#include "pch.h"
#include "UI.h"

void UserInterface::draw(sf::RenderTarget& target, sf::RenderStates) const
{
	for (auto&& layout : m_Layouts) {
		target.draw(*layout);
	}
}

void UserInterface::recalculatePositionVariable()
{
	float min_x{ std::numeric_limits<float>::max() };
	float min_y{ std::numeric_limits<float>::max() };

	for (auto&& layout : m_Layouts) {
		const sf::Vector2f curr_layout_pos(layout->getPosition());

		if (min_x > curr_layout_pos.x)	min_x = curr_layout_pos.x;
		if (min_y > curr_layout_pos.y)	min_y = curr_layout_pos.y;
	}

	m_Position = sf::Vector2f(min_x, min_y);
}

UserInterface::UserInterface()
	: Widget(std::nullopt), ActionTarget(Configuration::gui_inputs)
{

}

UserInterface::~UserInterface()
{
}

void UserInterface::setPositionAtIndex(const sf::Vector2f& pos, unsigned int index)
{
	m_Layouts.at(index)->setPosition(pos);
	recalculatePositionVariable();
}

void UserInterface::setPositionAtIndex(float x, float y, unsigned int index)
{
	setPositionAtIndex(sf::Vector2f(x, y), index);
}

void UserInterface::processEvent(const sf::Event& sfevent)
{
	for (auto&& layout : m_Layouts) {
		layout->processEvent(sfevent);
	}
}

sf::Vector2f UserInterface::getSize() const
{
	float max_x{}, min_x{ std::numeric_limits<float>::max() };
	float max_y{}, min_y{ std::numeric_limits<float>::max() };

	for (auto&& layout : m_Layouts) {
		const sf::Vector2f curr_layout_size(layout->getSize());
		const sf::Vector2f curr_layout_pos(layout->getPosition());

		if (max_x < curr_layout_pos.x + curr_layout_size.x) max_x = curr_layout_pos.x + curr_layout_size.x;
		if (max_y < curr_layout_pos.y + curr_layout_size.y)	max_y = curr_layout_pos.y + curr_layout_size.y;

		if (min_x > curr_layout_pos.x)	min_x = curr_layout_pos.x;
		if (min_y > curr_layout_pos.y)	min_y = curr_layout_pos.y;
	}

	return sf::Vector2f(max_x - min_x, max_y - min_y);
}

void UserInterface::addLayout(std::unique_ptr<Layout> layout)
{
	m_Layouts.push_back(std::move(layout));

	recalculatePositionVariable();
}

void UserInterface::update(const sf::Time& deltaTime)
{
	for (auto&& layout : m_Layouts) {
		layout->update(deltaTime);
	}
}


void UserInterface::bind(int key, const FuncType& callback)
{
	ActionTarget::bind(key, callback);
}

void UserInterface::unbind(int key)
{
	ActionTarget::unbind(key);
}

