#include "Label.h"

void Label::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_Text, states);
}

Label::Label(std::string_view text, Widget* parent)
	: Widget(parent)
{

	m_Font = Configuration::fonts.get(Configuration::Fonts::SpaceGui);
	m_Text.setFont(m_Font);
	m_Text.setCharacterSize(25);
	m_Text.setString(text.data());
}

Label::Label(std::string_view text, const sf::Font& font, unsigned int charSize, Widget* parent)
	: Widget(parent)
{
	m_Text.setFont(font);
	m_Text.setCharacterSize(charSize);
	m_Text.setString(text.data());
}

sf::Vector2f Label::getSize() const
{
	sf::FloatRect rect = m_Text.getGlobalBounds();
	return sf::Vector2f(rect.width, rect.height);
}

void Label::setPosition(const sf::Vector2f& pos)
{
	m_Position = pos;
	m_Text.setPosition(m_Position);
}

void Label::setPosition(float x, float y)
{
	m_Position.x = x;
	m_Position.y = y;
	m_Text.setPosition(m_Position);
}

void Label::setTextColor(const sf::Color& color)
{
	m_Text.setFillColor(color);
}

unsigned int Label::getCharacterSize() const
{
	return m_Text.getCharacterSize();
}
