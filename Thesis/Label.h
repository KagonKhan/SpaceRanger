#pragma once
#include "Widget.h"

namespace GUI
{	
	/* Simple class, printing text on screen */
	/* Wrapper for sf::Text */
	class Label : public Widget
	{
	private:
		sf::Text m_Text;
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	public:
		Label(const Label&) = delete;
		Label& operator=(const Label&) = delete;

		Label(std::string_view text, Widget* parent = nullptr);
		virtual ~Label();

		/* Set text and update shape */
		void setText(std::string_view text);
		/* Set size and update shape */
		void setCharacterSize(unsigned int size);
		void setTextColor(const sf::Color& color);
		unsigned int getCharacterSize() const;

		/* Get global bounds and convert to vec2f */
		virtual sf::Vector2f getSize() const override;

	};

}