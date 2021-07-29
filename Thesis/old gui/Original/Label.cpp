#include "Label.h"
#include "Configuration.h"

namespace GUI
{
	
	Label::Label(std::string_view text, Widget* parent)
		: Label(text, Configuration::fonts.get(Configuration::Fonts::Gui), parent)
	{

	}

	Label::Label(std::string_view text, sf::Font& font, Widget* parent) 
		: Widget(parent)
	{
		m_Text.setFont(font);
		setText(text);
		setTextColor(Configuration::Colors::label_text);
	}

	Label::~Label()
	{

	}

	void Label::setText(std::string_view text)
	{
		m_Text.setString(text.data());
		updateShape();
	}

	void Label::setCharacterSize(unsigned int size)
	{
		m_Text.setCharacterSize(size);
		updateShape();
	}

	void Label::setTextColor(const sf::Color& color)
	{
		m_Text.setFillColor(color);
	}

	unsigned int Label::getCharacterSize() const
	{
		return m_Text.getCharacterSize();
	}

	sf::Vector2f Label::getSize() const
	{
		sf::FloatRect rect = m_Text.getGlobalBounds();
		return sf::Vector2f(rect.width, rect.height);
	}

	void Label::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		/* Each widget has its own position, so we translate the transform matrix by relative position */
		states.transform.translate(m_Position);
		target.draw(m_Text, states);
	}
}