#include "pch.h"
#include "Checkbox.h"


Checkbox::Checkbox(std::string_view text, Widget* parent)
	: TextButton(text, parent), m_IsChecked(false)
{
	setFillBoxColor(sf::Color(200, 200, 200, 255));
	setFillColor(sf::Color::Transparent);
	setOutlineBoxColor(sf::Color::Black);

	setOutlineBoxThickness(2);
	setBoxSize(25);

	adjustSize();
}

/* TODO: Finish the constructor */
Checkbox::Checkbox(std::string_view text, const sf::Font& font, unsigned int charSize, unsigned int size, float outlineThicc, const sf::Color& outlinecolor, const sf::Color& fillColor, const sf::Color& textColor, Widget* parent)
	: TextButton(text, parent)
{
}

void Checkbox::processEvent(const sf::Event& sfevent)
{
	bool res = false;
	if (sfevent.type == sf::Event::MouseButtonReleased) {
		sf::FloatRect rect = m_Shape.getGlobalBounds();
		rect.width += m_BoxShape.getSize().x;
		if (rect.contains(sfevent.mouseButton.x, sfevent.mouseButton.y)) {
			on_click(sfevent, *this);
			m_IsChecked = !m_IsChecked;
			res = true;
		}
	}
	else if (sfevent.type == sf::Event::MouseMoved) {
		const sf::Vector2f mouse_pos(sfevent.mouseMove.x, sfevent.mouseMove.y);

		int old_status = m_Status;
		m_Status = Status::Idle;

		sf::FloatRect rect = m_Shape.getGlobalBounds();
		rect.width += m_BoxShape.getSize().x;

		if (rect.contains(mouse_pos))
			m_Status |= Status::Hover;
		if ((old_status & Status::Hover) && !(m_Status & Status::Hover))
			onMouseLeft();
		else if (!(old_status & Status::Hover) && (m_Status & Status::Hover))
			onMouseEntered();
	}

}

void Checkbox::onMouseEntered()
{
	const float light = 0.9f;
	m_BoxShape.setFillColor(sf::Color(m_FillColorBox.r * light, m_FillColorBox.g * light, m_FillColorBox.b * light));
	m_Shape.setFillColor(sf::Color(0,0,0,100));
}

void Checkbox::onMouseLeft()
{
	m_BoxShape.setFillColor(m_FillColorBox);
	m_Shape.setFillColor(m_FillColor);
}

void Checkbox::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_Shape, states);
	target.draw(m_BoxShape, states);
	target.draw(m_Label, states);

	if (m_IsChecked)
		target.draw(cross, states);
}

void Checkbox::setPosition(const sf::Vector2f& pos)
{
	m_Position = pos;
	m_Shape.setPosition(m_Position);
	updateTextPosition();
	//m_Label.setPosition(m_Position);

	float y = m_Shape.getPosition().y + (m_Shape.getSize().y - m_BoxShape.getSize().y) / 2.f;
	m_BoxShape.setPosition(m_Position.x + m_Shape.getSize().x - m_BoxShape.getSize().x, y);
	
	cross.setPosition(m_BoxShape.getPosition(), m_BoxShape.getSize());

}

void Checkbox::setPosition(float x, float y)
{
	setPosition(sf::Vector2f(x,y));
}

void Checkbox::setOutlineBoxColor(const sf::Color& color)
{
	m_OutlineColorBox = color;
	m_BoxShape.setOutlineColor(m_OutlineColorBox);
}

void Checkbox::setFillBoxColor(const sf::Color& color)
{
	m_FillColorBox = color;
	m_BoxShape.setFillColor(color);
}

void Checkbox::setOutlineBoxThickness(float thickness)
{
	m_BoxShape.setOutlineThickness(thickness);
	adjustSize();
}

void Checkbox::setBoxSize(float size)
{
	m_BoxShape.setSize(sf::Vector2f(size, size));
	adjustSize();
}

void Checkbox::adjustSize()
{
	sf::Vector2f size(0, 0);
	size.x = m_Label.getSize().x + 2 * m_Label.getCharacterSize();
	size.y = m_Label.getSize().y + 1.5 * m_Label.getCharacterSize();

	if (m_MinWidth != 0 && size.x < m_MinWidth)
		size.x = m_MinWidth;
	if (m_MaxWidth != 0 && size.x > m_MaxWidth)
		size.x = m_MaxWidth;

	if (m_MinHeight != 0 && size.y < m_MinHeight)
		size.y = m_MinHeight;
	if (m_MaxHeight != 0 && size.y > m_MaxHeight)
		size.y = m_MaxHeight;
	


	m_Shape.setSize(size);
}

sf::Vector2f Checkbox::getSize() const
{
	return m_Shape.getSize() + sf::Vector2f(m_BoxShape.getSize().x, 0);
}

void Checkbox::updateTextPosition()
{
	sf::Vector2f position((m_Shape.getSize() - m_Label.getSize()) / 2.f);
	position += m_Shape.getPosition();
	m_Label.setPosition(position);
}

void Checkbox::setSize(const sf::Vector2f& size)
{
	m_Shape.setSize(size);
	updateTextPosition();
	sf::Vector2f box_pos(m_Shape.getPosition());
	box_pos.x += m_Shape.getSize().x - m_BoxShape.getSize().x;
	box_pos.y += float(m_Shape.getSize().y - m_BoxShape.getSize().y);
	m_BoxShape.setPosition(box_pos);
}

bool Checkbox::getIsChecked() const
{
	return m_IsChecked;
}

void Checkbox::setIsChecked(bool checked)
{
	m_IsChecked = checked;
}

 