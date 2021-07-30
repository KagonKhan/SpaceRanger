#include "pch.h"
#include "UI.h"

void UI::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
		target.draw(*_layout, states);
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
	
	_layout->processEvent(sfevent);

	ActionTarget::processEvent(sfevent);
	return true;
}

void UI::addLayout(Layout* layout)
{
	_layout = layout;
	_layout->updateShape();
}

void UI::setLayoutPosition(sf::Vector2f position)
{
	m_Position = position;
	_layout->setPosition(position);
	_layout->updateShape();
}

void UI::bind(int key, const FuncType& callback)
{
	ActionTarget::bind(key, callback);
}

void UI::unbind(int key)
{
	ActionTarget::unbind(key);
}
