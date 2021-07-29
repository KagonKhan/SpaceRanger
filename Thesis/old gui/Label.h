#pragma once
#include "Widget.h"

namespace GUI
{	
	/* Simple class, printing text on screen */
	/* Wrapper for sf::Text */
	class Label : virtual public Widget
	{
	private:
		sf::Text m_Text;
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	public:
		Label(const Label&) = delete;
		Label& operator=(const Label&) = delete;

		Label(std::string_view text, Widget* parent = nullptr);
		Label(std::string_view text, sf::Font& font, Widget* parent = nullptr);
		virtual ~Label();


	};

}