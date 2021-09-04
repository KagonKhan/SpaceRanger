#include "pch.h"
#include "Button.h"

Button::Button(opt_ref parent)
	: Widget(parent), m_Status(Status::Idle), on_click([](const sf::Event&, Button&)->void {})
{
	puts("Button\t\tctor");
}

Button::~Button()
{
	puts("Button\t\tdtor");
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




