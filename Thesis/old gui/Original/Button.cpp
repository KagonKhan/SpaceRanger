#include "..\..\..\..\SFML playground\SFML playground\Button.h"
#include "Button.h"

namespace GUI
{
	/* Init the default function as null */
	Button::FuncType Button::defaultFunc = [](const sf::Event&, Button&)->void {};

	Button::Button(Widget* parent)
		: Widget(parent), on_click(defaultFunc), m_Status(Status::Idle)
	{
	}

	Button::~Button()
	{
	}

	bool Button::processEvent(const sf::Event& sfevent, const sf::Vector2f& parent_pos)
	{
		bool res = false;

		/* Check if button released inside the button area */
		if (sfevent.type == sf::Event::MouseButtonReleased) {
			const sf::Vector2f pos = m_Position + parent_pos;
			const sf::Vector2f size = getSize();

			sf::FloatRect rect(pos.x, pos.y, size.x, size.y);

			if (rect.contains(sfevent.mouseButton.x, sfevent.mouseButton.y)) {
				on_click(sfevent, *this);
				res = true;
			}

		}
		/* Check if mouse was moved inside or outside the button, based on button status */
		else if (sfevent.type == sf::Event::MouseMoved) {
			const sf::Vector2f pos = m_Position + parent_pos;
			const sf::Vector2f size = getSize();

			sf::FloatRect rect(pos.x, pos.y, size.x, size.y);
			const sf::Vector2f mouse_pos(sfevent.mouseMove.x, sfevent.mouseMove.y);

			int old_status = m_Status;
			m_Status = Status::Idle;

			if (rect.contains(mouse_pos))
				m_Status |= Status::Hover;

			if ((old_status & Status::Hover) && !(m_Status & Status::Hover))
				onMouseLeft();
			else if (!(old_status & Status::Hover) && (m_Status & Status::Hover))
				onMouseEntered();

		}
		
		return res;
	}

	bool Button::processEvent(const sf::Event& sfevent)
	{
		return false;
	}

	void Button::onMouseEntered()
	{
	}

	void Button::onMouseLeft()
	{
	}
}