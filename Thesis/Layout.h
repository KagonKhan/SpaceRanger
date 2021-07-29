#pragma once
#include "Widget.h"


class Layout : public Widget
{

protected:
	std::vector<Widget*> m_Widgets;
	float padding;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	virtual void updateShape() = 0;

public:
	Layout(Layout&) = delete;
	Layout& operator=(Layout&) = delete;

	Layout(float padding, Widget* parent = nullptr);
	virtual ~Layout();

	sf::Vector2f getSize() const override final;

	void setPosition(sf::Vector2f position);

};


class VerticalLayout : public Layout
{
private:
	void updateShape();

public:
	VerticalLayout(VerticalLayout&) = delete;
	VerticalLayout& operator=(VerticalLayout&) = delete;

	VerticalLayout(Widget* parent = nullptr);
	virtual ~VerticalLayout();

	bool processEvent(const sf::Event& sfevent);
	void add(Widget* widget);

};

class HorizontalLayout : public Layout
{
private:
	void updateShape();

public:
	HorizontalLayout(HorizontalLayout&) = delete;
	HorizontalLayout& operator=(HorizontalLayout&) = delete;

	HorizontalLayout(Widget* parent = nullptr);
	virtual ~HorizontalLayout();

	bool processEvent(const sf::Event& sfevent);
	void add(Widget* widget);

};