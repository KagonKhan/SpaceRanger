#pragma once
#include "Button.h"
#include "Label.h"

namespace GUI {
	/* Button + Label class */
	class TextButton : public Button
	{
	private:
		sf::RectangleShape m_Shape;
		Label m_Label;

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;


	public:
		TextButton(const TextButton&) = delete;
		TextButton& operator=(const TextButton&) = delete;

		TextButton(std::string_view text, Widget* parent = nullptr);
		TextButton(std::string_view text, sf::Font& font, Widget* parent = nullptr);
		virtual ~TextButton();	
	};

}