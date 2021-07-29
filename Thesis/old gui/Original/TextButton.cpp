#include "..\..\..\..\SFML playground\SFML playground\Button.h"
#include "TextButton.h"
#include "Configuration.h"
namespace GUI {

	TextButton::TextButton(std::string_view text, Widget* parent)
		: TextButton(text, Configuration::fonts.get(Configuration::Gui), parent)
	{

	}

	TextButton::TextButton(std::string_view text, sf::Font& font, Widget* parent)
		: Button(parent), m_Label(text, font, this)
	{
		setFillColor(sf::Color(86, 20, 19));
		setOutlineColor(sf::Color(86, 20, 19));
		setOutlineThickness(5);
	}


	TextButton::~TextButton()
	{
	}

	void TextButton::setText(std::string_view text)
	{
		m_Label.setText(text);
	}

	void TextButton::setCharacterSize(unsigned int size)
	{
		m_Label.setCharacterSize(size);
	}

	void TextButton::setTextColor(const sf::Color& color)
	{
		m_Label.setTextColor(color);
	}

	void TextButton::setFillColor(const sf::Color& color)
	{
		m_FillColor = color;
		m_Shape.setFillColor(m_FillColor);
	}

	void TextButton::setOutlineColor(const sf::Color& color)
	{
		m_OutlineColor = color;
		m_Shape.setOutlineColor(m_OutlineColor);
	}

	void TextButton::setOutlineThickness(float thickness)
	{
		m_Shape.setOutlineThickness(thickness);
	}

	sf::Vector2f TextButton::getSize() const
	{
		sf::FloatRect rect = m_Shape.getGlobalBounds();
		return sf::Vector2f(rect.width, rect.height);
	}


	void TextButton::updateShape()
	{
		sf::Vector2f label_size = m_Label.getSize();
		unsigned int char_size = m_Label.getCharacterSize();
		m_Shape.setSize(sf::Vector2f(2 * char_size + label_size.x, 2 * char_size + label_size.y));
		m_Label.setPosition(char_size, char_size);

		Widget::updateShape();
	}

	bool TextButton::processEvent(const sf::Event& sfevent)
	{
		return false;
	}

	void TextButton::onMouseEntered()
	{
		const float light = 1.4f;
		m_Shape.setOutlineColor(sf::Color(m_OutlineColor.r * light, m_OutlineColor.g * light, m_OutlineColor.b * light));
		m_Shape.setFillColor(sf::Color(m_FillColor.r * light, m_FillColor.g * light, m_FillColor.b * light));

	}

	void TextButton::onMouseLeft()
	{
		m_Shape.setOutlineColor(m_OutlineColor);
		m_Shape.setFillColor(m_FillColor);
	}

	void TextButton::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform.translate(m_Position);
		target.draw(m_Shape, states);
		target.draw(m_Label, states);
	}
}