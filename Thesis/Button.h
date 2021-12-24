#pragma once
#include "Widget.h"
#include "Label.h"

class Button :
	public Widget
{
protected:
	enum class Status	{ Idle = 0, Hover = 1, HoverAndPressed = 2 };
	Status m_Status		{ Status::Idle };
	using FuncType = std::function<void(const sf::Event& sfevent, Button& self)>;

	virtual void processEvent(const sf::Event& sfevent) override = 0;
	virtual void onMouseEntered();
	virtual void onMouseLeft();

public:
	Button(opt_ref parent);


	virtual std::string readValue();

	FuncType on_click = { [](const sf::Event&, Button&)->void {} };
};
