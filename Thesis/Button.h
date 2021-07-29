#pragma once
#include "Widget.h"
#include "Label.h"
#include <functional>

class Button :
	public Widget
{
protected:
	int m_Status;
	enum Status { Idle = 0, Hover = 1, Pressed = 2 };

	float m_MinWidth, m_MinHeight, m_MaxWidth, m_MaxHeight;

	virtual bool processEvent(const sf::Event& sfevent);
	virtual void onMouseEntered();
	virtual void onMouseLeft();

public:
	Button(const Button&) = delete;
	Button& operator=(const Button&) = delete;

	Button(Widget* parent = nullptr);
	Button(float minwidth, float minheight, float maxwidth, float maxheigth, Widget* parent = nullptr);

	using FuncType = std::function<void(const sf::Event& sfevent, Button& self)>;
	static FuncType defaultFunc;
	FuncType on_click;


};



class TextButton :
	public Button
{
private:
	bool processEvent(const sf::Event& sfevent) override final;
	void onMouseEntered() override final;
	void onMouseLeft() override final;

	sf::RectangleShape m_Shape;
	Label m_Label;
	sf::Color m_OutlineColor, m_FillColor;


	void draw(sf::RenderTarget& target, sf::RenderStates states) const override final;
	void updateTextPosition();

public:
	TextButton(const TextButton&) = delete;
	TextButton& operator=(const TextButton&) = delete;

	TextButton(std::string_view text, Widget* parent = nullptr);
	TextButton(std::string_view text, const sf::Font& font, unsigned int charSize, const sf::Vector2f& size,
		float outlineThicc, const sf::Color& outlinecolor, const sf::Color& fillColor, const sf::Color& textColor,
		float minwidth, float minheight, float maxwidth, float maxheigth,
		Widget* parent = nullptr);


	void setPosition(const sf::Vector2f& pos) override final;
	void setPosition(float x, float y) override final;
	void setOutlineColor(const sf::Color& color);
	void setFillColor(const sf::Color& color);
	void setTextColor(const sf::Color& color);
	void setOutlineThickness(float thickness);
	void setSize(const sf::Vector2f& size);
	// Automatically calculate size of the button, based on label
	void adjustSize();

	sf::Vector2f getSize() const override final;
};