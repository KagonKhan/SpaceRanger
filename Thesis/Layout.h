#pragma once
#include "Widget.h"
#include "Checkbox.h"

class Layout 
	: public Widget
{

protected:
	std::vector<Widget*> m_Widgets;
	float padding;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:
	virtual void updateShape() = 0;
	Layout(Layout&) = delete;
	Layout& operator=(Layout&) = delete;

	Layout(float padding, Widget* parent = nullptr);
	virtual ~Layout();

	virtual sf::Vector2f getSize() const =0;

	void setPosition(sf::Vector2f position);
	void add(Widget* widget);

	Widget* getAt(unsigned int index) const;

	virtual void update(const sf::Time& deltaTime);


	std::vector<Widget*>& getWidgets();
};


class VerticalLayout 
	: public Layout
{
private:
	void updateShape();

public:
	VerticalLayout(VerticalLayout&) = delete;
	VerticalLayout& operator=(VerticalLayout&) = delete;

	VerticalLayout(Widget* parent = nullptr);
	virtual ~VerticalLayout();

	virtual void processEvent(const sf::Event& sfevent) override;

	virtual sf::Vector2f getSize() const override final;
};

class VerticalScrollingLayout
	: public VerticalLayout
{
private:

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override final;
	void draw();

	sf::RenderTexture m_ViewableAreaTexture;
	sf::Sprite m_ViewableAreaSprite;
	sf::FloatRect m_ViewableArea;
	float m_MaxScrollSpeed;
	float m_CurrentSpeed;

public:
	VerticalScrollingLayout(VerticalScrollingLayout&) = delete;
	VerticalScrollingLayout& operator=(VerticalScrollingLayout&) = delete;

	VerticalScrollingLayout(Widget* parent = nullptr);
	virtual ~VerticalScrollingLayout();

	void processEvent(const sf::Event& sfevent) override final;

	void setViewableArea(const sf::Vector2f& area);
	void setMaxScrollSpeed(float speed);

	void update(const sf::Time& deltaTime) override final;
};



class HorizontalLayout 
	: public Layout
{
private:
	void updateShape();

public:
	HorizontalLayout(HorizontalLayout&) = delete;
	HorizontalLayout& operator=(HorizontalLayout&) = delete;

	HorizontalLayout(Widget* parent = nullptr);
	virtual ~HorizontalLayout();

	void processEvent(const sf::Event& sfevent);

	virtual sf::Vector2f getSize() const override final;
};