#include "TextButton.h"

namespace GUI {

	TextButton::TextButton(std::string_view text, Widget* parent)
		: TextButton(text, Configuration::fonts.get(Configuration::Gui), parent)
	{

	}

	TextButton::TextButton(std::string_view text, sf::Font& font, Widget* parent)
		: Button(parent), m_Label(text, font, this)
	{
		
	}


	TextButton::~TextButton()
	{
	}

	
	void TextButton::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{

		target.draw(m_Shape, states);
		target.draw(m_Label, states);
	}
}