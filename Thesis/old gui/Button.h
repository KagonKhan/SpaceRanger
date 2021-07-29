#pragma once
#include "Widget.h"
#include <functional>

namespace GUI {
	/* Virtual class, template for specific types of buttons */
	class Button : public Widget
	{
	private:

	public:
		Button(const Button&) = delete;
		Button& operator=(const Button&) = delete;

		using FuncType = std::function<void(const sf::Event& event, Button& self)>;
		static FuncType defaultFunc;

		Button(Widget* parent = nullptr);
		virtual ~Button();

		FuncType on_click;
	};
}