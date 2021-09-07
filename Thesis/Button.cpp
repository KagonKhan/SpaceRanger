#include "pch.h"
#include "Button.h"

Button::Button(opt_ref parent)
	: Widget(parent), m_Status(Status::Idle), on_click([](const sf::Event&, Button&)->void {})
{

}

Button::~Button()
{

}

std::string Button::readValue()
{
	return std::string();
}

void Button::processEvent(const sf::Event&)
{
}

void Button::onMouseEntered()
{
}

void Button::onMouseLeft()
{
}




