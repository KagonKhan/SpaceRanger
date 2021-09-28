#pragma once
#include "Button.h"
#include "Checkbox.h"
#include "Label.h"


class CheckboxButton :
	public Button
{
private:
	void draw(sf::RenderTarget& target, sf::RenderStates) const override;

	sf::RectangleShape						m_Shape;
	sf::Color								m_OutlineColor;
	sf::Color								m_FillColor;
	float									m_Padding		{ 5.f };
	Label									m_Label;
	Checkbox								m_Checkbox;
	sf::Color								m_CheckboxColor	{ 200,200,200,200 };



	void processEvent(const sf::Event& sfevent) override;
	void onMouseEntered() override;
	void onMouseLeft() override;

	void reposition();
	void recalculateCheckboxPosition();
	void recalculateTextPosition();

public:

	CheckboxButton(opt_ref parent, const sf::Vector2f& size, const sf::Color& fillColor,
		std::string_view text, const sf::Font& font, unsigned int charSize = 25,
		float boxSize = 25.f);




#pragma region SETTERS / GETTERS

	/* CHECKBOX SETTERS */
	void setCheckboxFillColor(const sf::Color& color);

	/* BUTTON SETTERS */
	void setPosition(const sf::Vector2f& pos) override;
	void setFillColor(const sf::Color& color);

	



	void setSize(const sf::Vector2f& size)				{		m_Shape.setSize(size);					  reposition(); }
	void setString(const std::string& string)			{		m_Label.setString(string);				  reposition(); }
	void setFont(const sf::Font& font)					{		m_Label.setFont(font);					  reposition(); }
	void setCharacterSize(unsigned int size)			{		m_Label.setCharacterSize(size);			  reposition(); }
	void setLetterSpacing(float factor)					{		m_Label.setLetterSpacing(factor);		  reposition(); }
	void setTextStyle(sf::Uint32 style)					{		m_Label.setStyle(style);				  reposition(); }
	void setCheckboxSize(float size)					{		m_Checkbox.setSize(size);								}
	void setCheckboxOutline(float thickness)			{		m_Checkbox.setOutlineThickness(thickness);				}
	void setOutlineThickness(float thickness)			{		m_Shape.setOutlineThickness(thickness);					}
	sf::Vector2f getSize() const						{		return m_Shape.getSize();								}
	void setTextFillColor(const sf::Color& color)		{		m_Label.setFillColor(color);							}
	void setTextOutlineColor(const sf::Color& color)	{		m_Label.setOutlineColor(color);							}
	void setTextOutlineThickness(float thickness)		{		m_Label.setOutlineThickness(thickness);					}
	unsigned int getCharacterSize() const				{		return m_Label.getCharacterSize();						}


#pragma endregion

};
