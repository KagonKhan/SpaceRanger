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
		sf::Color m_FillColor, m_OutlineColor;

		void updateShape()override;
		virtual void onMouseEntered() override;
		virtual void onMouseLeft() override;

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;


	public:
		TextButton(std::string_view text, Widget* parent = nullptr);
		virtual ~TextButton();

		void setText(std::string_view text);
		void setCharacterSize(unsigned int size);
		void setTextColor(const sf::Color& color);
		void setFillColor(const sf::Color& color);
		void setOutlineColor(const sf::Color& color);
		void setOutlineThickness(float thickness);

		virtual sf::Vector2f getSize() const override;
	};

}