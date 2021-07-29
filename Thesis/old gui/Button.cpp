#include "Button.h"

namespace GUI
{
	/* Init the default function as null */
	Button::FuncType Button::defaultFunc = [](const sf::Event&, Button&)->void {};

	Button::Button(Widget* parent)
		: Widget(parent), on_click(defaultFunc)
	{
	}

	Button::~Button()
	{
	}

	
}