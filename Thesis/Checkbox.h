#pragma once
#include "Button.h"
#include "Label.h"


/* 
	TODO: 
		- Cross class could be better, draw "thick" lines as in quads instead of lines?
		- Positioning and pressable area could use some work
	
*/
class Checkbox :
	public TextButton
{
private:

	sf::RectangleShape m_BoxShape;

	sf::Color m_OutlineColorBox, m_FillColorBox;

	bool m_IsChecked;
	struct Cross : sf::Drawable{
	private:
		sf::VertexArray shape;
	public:
		Cross() : shape(sf::Lines, 4) {
			setColor(sf::Color::Black);
		}

		void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
			target.draw(shape, states);
		}
		
		void setPosition(const sf::Vector2f& pos, const sf::Vector2f& size) {
			shape[0].position = pos;
			shape[1].position = pos + size;
			shape[2].position = sf::Vector2f(pos.x + size.x, pos.y);
			shape[3].position = sf::Vector2f(pos.x, pos.y + size.y);
		}
		void setColor(const sf::Color& color) {
			shape[0].color = color;
			shape[1].color = color;
			shape[2].color = color;
			shape[3].color = color;
		}
	} cross;


	void processEvent(const sf::Event& sfevent) override final;
	void onMouseEntered() override final;
	void onMouseLeft() override final;


	void draw(sf::RenderTarget& target, sf::RenderStates states) const override final;

public:
	Checkbox(const Checkbox&) = delete;
	Checkbox& operator=(const Checkbox&) = delete;

	Checkbox(std::string_view text, Widget* parent = nullptr);
	Checkbox(std::string_view text, const sf::Font& font, unsigned int charSize, unsigned int size,
		float outlineThicc, const sf::Color& outlinecolor, const sf::Color& fillColor, const sf::Color& textColor,
		Widget* parent = nullptr);


	void setPosition(const sf::Vector2f& pos) override final;
	void setPosition(float x, float y) override final;
	void setSize(const sf::Vector2f& size) override final;

	void setOutlineBoxColor(const sf::Color& color);
	void setFillBoxColor(const sf::Color& color);

	void setOutlineBoxThickness(float thickness);

	void setBoxSize(float size);

	// Automatically calculate size of the button, based on label
	void adjustSize() override;

	sf::Vector2f getSize() const override final;

	void updateTextPosition();

	bool getIsChecked() const;
	void setIsChecked(bool checked);

};

