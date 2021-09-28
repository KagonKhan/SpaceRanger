#include "pch.h"
#include "CheckboxButton.h"

void CheckboxButton::draw(sf::RenderTarget& target, sf::RenderStates) const
{
	target.draw(m_Shape);
	target.draw(m_Label);
	target.draw(m_Checkbox);
}

CheckboxButton::CheckboxButton(opt_ref parent, const sf::Vector2f& size, const sf::Color& fillColor, std::string_view text, const sf::Font& font, unsigned int charSize, float boxSize)
	: Button(parent), m_Shape(size), m_Label(opt_ref(*this), text, font, charSize), m_Checkbox(boxSize)
{
	setFillColor(fillColor);
}


void CheckboxButton::processEvent(const sf::Event& sfevent)
{
	if (sfevent.type == sf::Event::MouseButtonPressed && m_Status == Status::Hover)
		m_Status = Status::HoverAndPressed;

	if (sfevent.type == sf::Event::MouseButtonReleased && m_Status == Status::HoverAndPressed && static_cast<sf::Mouse::Button>(sfevent.key.code) == sf::Mouse::Left) {
		if (m_Shape.getGlobalBounds().contains(static_cast<float>(sfevent.mouseButton.x), static_cast<float>(sfevent.mouseButton.y))) {
			m_Checkbox.setIsChecked(!m_Checkbox.getIsChecked());
			on_click(sfevent, *this);
		}
	}
	else if (sfevent.type == sf::Event::MouseMoved) {
		const sf::Vector2f mouse_pos(static_cast<float>(sfevent.mouseMove.x), static_cast<float>(sfevent.mouseMove.y));

		Status old_status = m_Status;
		m_Status = Status::Idle;

		/* If pressed and still hovering, keep pressed */
		if (old_status == Status::HoverAndPressed && m_Shape.getGlobalBounds().contains(mouse_pos))
			m_Status = Status::HoverAndPressed;
		/* else check if just hovering */
		else if (m_Shape.getGlobalBounds().contains(mouse_pos))
			m_Status = Status::Hover;
		/* if neither hovering nor pressed = mouse left */
		if ((old_status == Status::Hover || old_status == Status::HoverAndPressed) && !(m_Status == Status::Hover || m_Status == Status::HoverAndPressed))
			onMouseLeft();
		else if (!(old_status == Status::Hover) && (m_Status == Status::Hover))
			onMouseEntered();
	}
}

void CheckboxButton::onMouseEntered()
{
	m_Shape.setFillColor(sf::Color(m_FillColor * sf::Color(182, 182, 182)));
	m_Shape.setOutlineColor(sf::Color(m_OutlineColor * sf::Color(182, 182, 182)));

	m_Checkbox.setFillColor(m_CheckboxColor * sf::Color(170, 170, 170));
}

void CheckboxButton::onMouseLeft()
{
	m_Shape.setFillColor(m_FillColor);
	m_Shape.setOutlineColor(m_OutlineColor);

	m_Checkbox.setFillColor(m_CheckboxColor);
}

void CheckboxButton::reposition()
{
	recalculateTextPosition();
	recalculateCheckboxPosition();
}

void CheckboxButton::recalculateCheckboxPosition()
{
	sf::Vector2f box_pos;
	sf::Vector2f box_size(m_Checkbox.getSize());

	box_pos.x = m_Position.x + getSize().x - box_size.x - m_Padding;
	box_pos.y = m_Position.y + (getSize().y - box_size.y) / 2.f;

	m_Checkbox.setPosition(box_pos);

}

void CheckboxButton::recalculateTextPosition()
{
	sf::Vector2f label_pos;
	sf::Vector2f label_size(m_Label.getSize());

	label_pos.x = m_Position.x + m_Padding;
	label_pos.y = m_Position.y + (getSize().y - label_size.y) / 2.f;

	m_Label.setPosition(label_pos);
}




#pragma region SETTERS / GETTERS



/* CHECKBOX SETTERS */

void CheckboxButton::setCheckboxFillColor(const sf::Color& color)
{
	m_CheckboxColor = color;
	m_Checkbox.setFillColor(m_CheckboxColor);
}


/* BUTTON SETTERS */
void CheckboxButton::setPosition(const sf::Vector2f& pos)
{
	m_Position = pos;
	m_Shape.setPosition(m_Position);

	reposition();
}

void CheckboxButton::setFillColor(const sf::Color& color)
{
	m_FillColor = color;
	m_Shape.setFillColor(m_FillColor);
}

#pragma endregion