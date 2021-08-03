#pragma once
#include "Widget.h"
#include "Label.h"

class Button :
	public Widget
{
protected:
	int m_Status;
	bool m_IsVisible;
	bool m_IsActive;

	/* ID used to easily differentiate between many buttons in a layout */
	short int m_ID;
	enum Status { Idle = 0, Hover = 1, Pressed = 2 };

	float m_MinWidth, m_MinHeight, m_MaxWidth, m_MaxHeight;

	virtual bool processEvent(const sf::Event& sfevent);
	virtual void onMouseEntered();
	virtual void onMouseLeft();

public:
	Button(const Button&) = delete;
	Button& operator=(const Button&) = delete;

	Button(Widget* parent = nullptr, short int id =0);
	Button(float minwidth, float minheight, float maxwidth, float maxheigth, Widget* parent = nullptr, short int id = 0);

	using FuncType = std::function<void(const sf::Event& sfevent, Button& self)>;
	static FuncType defaultFunc;
	FuncType on_click;


	virtual bool getStatus() const ;
	short int getID() const;
	void setID(short int id);

	void setIsVisible(bool visible);
	bool getIsVisible() const;
	void setIsActive(bool active);
	bool getIsActive() const;
};



class TextButton :
	public Button
{
protected:
	virtual bool processEvent(const sf::Event& sfevent) override;
	virtual void onMouseEntered() override;
	virtual void onMouseLeft() override;

	sf::RectangleShape m_Shape;
	Label m_Label;
	sf::Color m_OutlineColor, m_FillColor;


	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	virtual void updateTextPosition();

public:
	TextButton(const TextButton&) = delete;
	TextButton& operator=(const TextButton&) = delete;

	TextButton(std::string_view text, Widget* parent = nullptr);
	TextButton(std::string_view text, const sf::Font& font, unsigned int charSize, const sf::Vector2f& size,
		float outlineThicc, const sf::Color& outlinecolor, const sf::Color& fillColor, const sf::Color& textColor,
		float minwidth, float minheight, float maxwidth, float maxheigth,
		Widget* parent = nullptr);


	virtual void setPosition(const sf::Vector2f& pos) override;
	virtual void setPosition(float x, float y) override;
	void setOutlineColor(const sf::Color& color);
	void setFillColor(const sf::Color& color);
	void setTextColor(const sf::Color& color);
	void setOutlineThickness(float thickness);
	void setSize(const sf::Vector2f& size);
	void setLetterSpacing(float spacing);
	// Automatically calculate size of the button, based on label
	virtual	void adjustSize();

	virtual sf::Vector2f getSize() const override;

};

/* TODO: Finish this class */
class SpriteButton :
	public Button
{
private:
	sf::Sprite m_Sprite;
	// maybe label
public:
	SpriteButton(const SpriteButton&) = delete;
	SpriteButton& operator=(const SpriteButton&) = delete;
	SpriteButton(Configuration::Textures tex_id, Widget* parent = nullptr);



	virtual sf::Vector2f getSize() const override;
};