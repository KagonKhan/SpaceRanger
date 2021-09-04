#pragma once
#include "Button.h"
#include "Checkbox.h"
#include "Label.h"


class CheckboxButton :
	public Button
{
private:
	void draw(sf::RenderTarget& target, sf::RenderStates) const override;

	sf::RectangleShape m_Shape;
	sf::Color m_OutlineColor, m_FillColor;
	float m_Padding;

	Label m_Label;
	Checkbox m_Checkbox;
	sf::Color m_CheckboxColor;


	void processEvent(const sf::Event& sfevent) override;
	void onMouseEntered() override;
	void onMouseLeft() override;

	void recalculateCheckboxPosition();
	void recalculateTextPosition();

public:

	CheckboxButton(opt_ref parent, const sf::Vector2f& size, const sf::Color& fillColor,
		std::string_view text, sf::Font& font, unsigned int charSize = 25,
		float boxSize = 25.f);
	virtual ~CheckboxButton();



#pragma region SETTERS / GETTERS

	/* CHECKBOX SETTERS */
	void setCheckboxSize(float size);
	void setCheckboxFillColor(const sf::Color& color);
	void setCheckboxOutline(float thickness);

	/* BUTTON SETTERS */
	void setPosition(const sf::Vector2f& pos) override;
	void setOutlineThickness(float thickness);
	void setFillColor(const sf::Color& color);
	void setSize(const sf::Vector2f& size);
	sf::Vector2f getSize() const;

	/* TEXT SETTERS */
	void setString(const std::string& string);
	void setFont(const sf::Font& font);
	void setCharacterSize(unsigned int size);
	void setLetterSpacing(float spacingFactor);
	void setTextStyle(sf::Uint32 style);
	void setTextFillColor(const sf::Color& color);
	void setTextOutlineColor(const sf::Color& color);
	void setTextOutlineThickness(float thickness);
	unsigned int getCharacterSize() const;


#pragma endregion

};
