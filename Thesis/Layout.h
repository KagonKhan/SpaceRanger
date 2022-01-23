#pragma once
#include "Widget.h"

class Layout :
	public Widget
{
private:
	friend class Widget;
protected:
	std::vector<Widget::ptr> m_Widgets;
	float m_Padding;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates) const override;
	virtual void updateShape() = 0;

public:
	Layout(opt_ref parent, float padding);
	virtual ~Layout();

	virtual void update(const sf::Time& deltaTime) = 0;
	void processEvent(const sf::Event& sfevent) override;

	void setPosition(const sf::Vector2f& pos) override;

	// move into this
	void add(Widget::ptr widget);
	Widget& getAt(unsigned int index) const;

	const std::vector<Widget::ptr>& getWidgets() const;
};

