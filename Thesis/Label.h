#pragma once
#include "Widget.h"

class Label : public Widget
{
private:
	sf::Text m_Text;
	sf::Font m_Font;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override final;

public:

	Label(const Label&) = delete;
	Label& operator=(const Label&) = delete;

	Label(std::string_view text, Widget* parent = nullptr);
	Label(std::string_view text, const sf::Font& font, unsigned int charSize, Widget* parent = nullptr);

	~Label() {};

	sf::Vector2f getSize() const override final;


	void setPosition(const sf::Vector2f& pos) override final;
	void setPosition(float x, float y) override final;

	void setTextColor(const sf::Color& color);

	unsigned int getCharacterSize() const;
};

