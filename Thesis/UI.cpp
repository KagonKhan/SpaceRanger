#include "pch.h"
#include "UI.h"

void UI::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(*_layout, states);
}

UI::UI(sf::RenderWindow& window, Widget* parent)
	: window(window), ActionTarget(Configuration::gui_inputs), _layout(nullptr)
{

}

UI::~UI()
{
}

sf::Vector2f UI::getSize() const
{
	return _layout->getSize();
}

void UI::processEvent(const sf::Event& sfevent)
{
	
	_layout->processEvent(sfevent);

	ActionTarget::processEvent(sfevent);
}

void UI::addLayout(Layout* layout, bool update)
{
	_layout = layout;
	if(update)
		_layout->updateShape();
}

void UI::setPosition(sf::Vector2f position)
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

void UI::update(const sf::Time& deltaTime)
{
	_layout->update(deltaTime);
}

const std::vector<Widget*>& UI::getWidgets() const
{
	return _layout->getWidgets();
}
