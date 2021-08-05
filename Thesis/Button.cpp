#include "pch.h"
#include "Button.h"

Button::FuncType Button::defaultFunc = [](const sf::Event&, Button&)->void {};

Button::Button(Widget* parent, short int id)
	: Widget(parent), m_MinWidth(0), m_MinHeight(0), m_MaxWidth(0), m_MaxHeight(0), m_ID(id), m_Status(Status::Idle)
{

}

Button::Button(float minwidth, float minheight, float maxwidth, float maxheigth, Widget* parent, short int id)
	: Widget(parent), m_MinWidth(minwidth), m_MinHeight(minheight), m_MaxWidth(maxwidth), m_MaxHeight(maxheigth), m_ID(id), m_Status(Status::Idle)
{

}

bool Button::getStatus() const
{
	return m_Status;
}

short int Button::getID() const
{
	return m_ID;
}

void Button::setID(short int id) 
{
	m_ID = id;
}

void Button::onMouseEntered()
{

}

void Button::onMouseLeft()
{

}

void Button::processEvent(const sf::Event& sfevent)
{

}










TextButton::TextButton(std::string_view text, Widget* parent)
	: Button(200, 100, 0, 0, parent), m_Label(text, this)
{
	m_FillColor = sf::Color::Red;
	m_Shape.setFillColor(m_FillColor);
	adjustSize();
}

TextButton::TextButton(std::string_view text, const sf::Font& font, unsigned int charSize, const sf::Vector2f& size,
	float outlineThicc, const sf::Color& outlinecolor, const sf::Color& fillColor, const sf::Color& textColor,
	float minwidth, float minheight, float maxwidth, float maxheigth, Widget* parent)

	: Button(minwidth, minheight, maxwidth, maxheigth, parent),
	m_Label(text, font, charSize, this)
{
	setOutlineColor(outlinecolor);
	setFillColor(fillColor);
	setTextColor(textColor);
	setOutlineThickness(outlineThicc);
	setSize(size);
} 

/* TODO: Buttons right now activate when button was RELEASED INSIDE THE BUTTON, might want to change later */
void TextButton::processEvent(const sf::Event& sfevent)
{
	bool res = false;
	if (sfevent.type == sf::Event::MouseButtonReleased) {
		if (m_Shape.getGlobalBounds().contains(sfevent.mouseButton.x, sfevent.mouseButton.y)) {
			on_click(sfevent, *this);
			res = true;
		}
	}
	else if (sfevent.type == sf::Event::MouseMoved) {
		const sf::Vector2f mouse_pos(sfevent.mouseMove.x, sfevent.mouseMove.y);

		int old_status = m_Status;
		m_Status = Status::Idle;

		if (m_Shape.getGlobalBounds().contains(mouse_pos))
			m_Status |= Status::Hover;
		if ((old_status & Status::Hover) && !(m_Status & Status::Hover))
			onMouseLeft();
		else if (!(old_status & Status::Hover) && (m_Status & Status::Hover))
			onMouseEntered();
	}
}

void TextButton::onMouseEntered()
{
	const float light = 1.4f;
	m_Shape.setOutlineColor(sf::Color(m_OutlineColor.r * light, m_OutlineColor.g * light, m_OutlineColor.b * light));
	m_Shape.setFillColor(sf::Color(m_FillColor.r * light, m_FillColor.g * light, m_FillColor.b * light));
}

void TextButton::onMouseLeft()
{
	m_Shape.setFillColor(m_FillColor);
	m_Shape.setOutlineColor(m_OutlineColor);
}

/* TODO: For some reason the text is not centered vertically, its y=0 is in the middle of the button IDK why for now don't care - it's a feature*/
void TextButton::updateTextPosition()
{
	sf::Vector2f position((m_Shape.getSize() - m_Label.getSize()) / 2.f);
	position += m_Shape.getPosition();
	m_Label.setPosition(position);
}

void TextButton::setPosition(const sf::Vector2f& pos)
{
	m_Position = pos;
	m_Shape.setPosition(m_Position);
	updateTextPosition();
}

void TextButton::setPosition(float x, float y)
{
	setPosition(sf::Vector2f(x,y));
}

void TextButton::setOutlineColor(const sf::Color& color)
{
	m_OutlineColor = color;
	m_Shape.setOutlineColor(m_OutlineColor);
}

void TextButton::setFillColor(const sf::Color& color)
{
	m_FillColor = color;
	m_Shape.setFillColor(m_FillColor);
}

void TextButton::setTextColor(const sf::Color& color)
{
	m_Label.setTextColor(color);
}

void TextButton::setOutlineThickness(float thickness)
{
	m_Shape.setOutlineThickness(thickness);
}

void TextButton::setSize(const sf::Vector2f& size)
{
	m_Shape.setSize(size);
	updateTextPosition();
}

/* TODO: maybe add a flag if I want to actually adjust button size automatically */
void TextButton::setLetterSpacing(float spacing)
{
	m_Label.setLetterSpacing(spacing);
	adjustSize();
}

void TextButton::adjustSize()
{
	sf::Vector2f size;
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

sf::Vector2f TextButton::getSize() const
{
	return m_Shape.getSize();
}

void TextButton::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_Shape, states);
	target.draw(m_Label, states);
}














void SpriteButton::processEvent(const sf::Event& sfevent)
{
	bool res = false;
	if (sfevent.type == sf::Event::MouseButtonReleased) {
		if (m_Sprite.getGlobalBounds().contains(sfevent.mouseButton.x, sfevent.mouseButton.y)) {
			on_click(sfevent, *this);
			res = true;
		}
	}
	else if (sfevent.type == sf::Event::MouseMoved) {
		const sf::Vector2f mouse_pos(sfevent.mouseMove.x, sfevent.mouseMove.y);

		int old_status = m_Status;
		m_Status = Status::Idle;

		if (m_Sprite.getGlobalBounds().contains(mouse_pos))
			m_Status |= Status::Hover;
		if ((old_status & Status::Hover) && !(m_Status & Status::Hover))
			onMouseLeft();
		else if (!(old_status & Status::Hover) && (m_Status & Status::Hover))
			onMouseEntered();
	}
}

void SpriteButton::onMouseEntered()
{
}

void SpriteButton::onMouseLeft()
{
}

void SpriteButton::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_Sprite);
}

SpriteButton::SpriteButton(Configuration::Textures tex_id, Widget* parent)
	: Button(parent)
{
	m_Sprite.setTexture(Configuration::textures.get(tex_id));
}

void SpriteButton::rotate(float angle)
{
	m_Sprite.rotate(angle);
}

void SpriteButton::setRotation(float angle)
{
	m_Sprite.setRotation(angle);
}

void SpriteButton::setScale(float factorX, float factorY)
{
	m_Sprite.setScale(factorX, factorY);
}

void SpriteButton::setScale(const sf::Vector2f& factors)
{
	m_Sprite.setScale(factors);
}

void SpriteButton::setPosition(const sf::Vector2f& pos)
{
	m_Position = pos;
	m_Sprite.setPosition(m_Position);
}

void SpriteButton::setPosition(float x, float y)
{
	m_Sprite.setPosition(sf::Vector2f(x,y));
}

sf::Vector2f SpriteButton::getSize() const
{
	return sf::Vector2f	(m_Sprite.getGlobalBounds().width, m_Sprite.getGlobalBounds().height);
}
