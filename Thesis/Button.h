#pragma once
#include "Widget.h"
#include <functional>

namespace GUI {
	/* Virtual class, template for specific types of buttons */
	class Button : public Widget
	{
	private:
		/* TODO: Expand this later - for now not really used*/
		enum Status {Idle = 0,  Hover = 1, Pressed = 2};
		int m_Status;

	protected:
		virtual bool processEvent(const sf::Event& sfevent, const sf::Vector2f& parent_pos) override;
		virtual void onMouseEntered();
		virtual void onMouseLeft();

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