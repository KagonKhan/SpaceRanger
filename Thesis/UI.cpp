#include "UI.h"

void UI::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (Layout* layout : _layouts)
		target.draw(*layout, states);
}

UI::UI(sf::RenderWindow& window, Widget* parent)
	: window(window), ActionTarget(Configuration::gui_inputs)
{

}

sf::Vector2f UI::getSize() const
{
	return sf::Vector2f(0, 0);
}

bool UI::processEvent(const sf::Event& sfevent)
{
	for (Layout* layout : _layouts)
		layout->processEvent(sfevent);

	ActionTarget::processEvent(sfevent);
	return true;
}

void UI::addLayout(Layout* layout)
{
	_layouts.emplace_back(layout);
}

void UI::setLayoutPosition(sf::Vector2f position)
{
	m_Position = position;
}

void UI::bind(int key, const FuncType& callback)
{
	ActionTarget::bind(key, callback);
}

void UI::unbind(int key)
{
	ActionTarget::unbind(key);
}
