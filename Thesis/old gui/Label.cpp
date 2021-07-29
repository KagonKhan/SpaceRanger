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
		
	}

	Label::~Label()
	{

	}

	

	void Label::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		/* Each widget has its own position, so we translate the transform matrix by relative position */
		
		target.draw(m_Text, states);
	}
}