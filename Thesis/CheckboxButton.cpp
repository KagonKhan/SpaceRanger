#include "pch.h"
#include "CheckboxButton.h"

void CheckboxButton::draw(sf::RenderTarget& target, sf::RenderStates) const
{
	target.draw(m_Shape);
	target.draw(m_Label);
	target.draw(m_Checkbox);
}

CheckboxButton::CheckboxButton(opt_ref parent, const sf::Vector2f& size, const sf::Color& fillColor, std::string_view text, sf::Font& font, unsigned int charSize, float boxSize)
	: Button(parent), m_Shape(size), m_Label(opt_ref(*this), text, font, charSize), m_Padding(5.f), m_Checkbox(boxSize), m_CheckboxColor(sf::Color(200, 200, 200))
{
	setFillColor(fillColor);
}

CheckboxButton::~CheckboxButton()
{
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
void CheckboxButton::setCheckboxSize(float size)
{
	m_Checkbox.setSize(size);
}

void CheckboxButton::setCheckboxFillColor(const sf::Color& color)
{
	m_CheckboxColor = color;
	m_Checkbox.setFillColor(m_CheckboxColor);
}

void CheckboxButton::setCheckboxOutline(float thickness)
{
	m_Checkbox.setOutlineThickness(thickness);
}




/* BUTTON SETTERS */
void CheckboxButton::setPosition(const sf::Vector2f& pos)
{
	m_Position = pos;
	m_Shape.setPosition(m_Position);

	recalculateCheckboxPosition();
	recalculateTextPosition();
}

void CheckboxButton::setOutlineThickness(float thickness)
{
	m_Shape.setOutlineThickness(thickness);
}

void CheckboxButton::setFillColor(const sf::Color& color)
{
	m_FillColor = color;
	m_Shape.setFillColor(m_FillColor);
}

void CheckboxButton::setSize(const sf::Vector2f& size)
{
	m_Shape.setSize(size);

	recalculateCheckboxPosition();
	recalculateTextPosition();
}

sf::Vector2f CheckboxButton::getSize() const
{
	return m_Shape.getSize();
}




/* TEXT SETTERS */
void CheckboxButton::setString(const std::string& string)
{
	m_Label.setString(string);
	recalculateTextPosition();
}

void CheckboxButton::setFont(const sf::Font& font)
{
	m_Label.setFont(font);
	recalculateTextPosition();
}

void CheckboxButton::setCharacterSize(unsigned int size)
{
	m_Label.setCharacterSize(size);
	recalculateTextPosition();
}

void CheckboxButton::setLetterSpacing(float spacingFactor)
{
	m_Label.setLetterSpacing(spacingFactor);
	recalculateTextPosition();
}

void CheckboxButton::setTextStyle(sf::Uint32 style)
{
	m_Label.setStyle(style);
	recalculateTextPosition();
}

void CheckboxButton::setTextFillColor(const sf::Color& color)
{
	m_Label.setFillColor(color);

}

void CheckboxButton::setTextOutlineColor(const sf::Color& color)
{
	m_Label.setOutlineColor(color);
}

void CheckboxButton::setTextOutlineThickness(float thickness)
{
	m_Label.setOutlineThickness(thickness);
}

unsigned int CheckboxButton::getCharacterSize() const
{
	return m_Label.getCharacterSize();
}

#pragma endregion