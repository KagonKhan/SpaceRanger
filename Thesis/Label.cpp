#include "pch.h"
#include "Label.h"

void Label::draw(sf::RenderTarget& target, sf::RenderStates) const
{
	target.draw(m_Text);
}

Label::Label()
	:Widget(std::nullopt)
{
}

Label::Label(opt_ref parent, std::string_view text, const sf::Font& font, unsigned int characterSize)
	: Widget(parent), m_Text(text.data(), font, characterSize)
{
	puts("Label\t\tctor");
}

Label::~Label()
{
	puts("Label\t\tdtor");
}


#pragma region SETTERS / GETTERS

void Label::setPosition(const sf::Vector2f& pos)
{
	
	m_Position = pos;
	m_Position.x -= m_Text.getLocalBounds().left;
	m_Position.y -= m_Text.getLocalBounds().top;
	m_Text.setPosition(m_Position);
}

sf::Vector2f Label::getSize() const
{
	return sf::Vector2f(m_Text.getGlobalBounds().width, m_Text.getGlobalBounds().height);
}

void Label::setString(const sf::String& string)
{
	m_Text.setString(string);
}

void Label::setFont(const sf::Font& font)
{
	m_Text.setFont(font);
}

void Label::setCharacterSize(unsigned int size)
{
	m_Text.setCharacterSize(size);
}

void Label::setLineSpacing(float spacingFactor)
{
	m_Text.setLineSpacing(spacingFactor);
}

void Label::setLetterSpacing(float spacingFactor)
{
	m_Text.setLetterSpacing(spacingFactor);
}

void Label::setStyle(sf::Uint32 style)
{
	m_Text.setStyle(style);
}

void Label::setFillColor(const sf::Color& color)
{
	m_Text.setFillColor(color);
}

void Label::setOutlineColor(const sf::Color& color)
{
	m_Text.setOutlineColor(color);
}

void Label::setOutlineThickness(float thickness)
{
	m_Text.setOutlineThickness(thickness);
}

unsigned int Label::getCharacterSize() const
{
	return m_Text.getCharacterSize();
}

sf::Color Label::getOutlineColor() const
{
	return m_Text.getOutlineColor();
}


#pragma endregion