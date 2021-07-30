#include "pch.h"
#include "Layout.h"
#include "Button.h"
/* ==============================    LAYOUT    ============================== */
void Layout::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (Widget* widget : m_Widgets)
		target.draw(*widget, states);

}


Layout::Layout(float padding, Widget* parent)
	: padding(padding)
{

}

Layout::~Layout()
{
}

sf::Vector2f Layout::getSize() const
{
	return sf::Vector2f(0, 0);
}

void Layout::setPosition(sf::Vector2f position)
{
	m_Position = position;
	updateShape();
}




/* ===========================    VERTICAL LAYOUT    =========================== */
void VerticalLayout::updateShape()
{
	float pos_y = m_Position.y;

	for (Widget* widget : m_Widgets) {
		sf::Vector2f size = widget->getSize();

		widget->setPosition(m_Position.x, pos_y);
		pos_y += size.y + padding;

	}
}

VerticalLayout::VerticalLayout(Widget* parent)
	: Layout(2.5f, parent)
{
}

VerticalLayout::~VerticalLayout()
{
}

bool VerticalLayout::processEvent(const sf::Event& sfevent)
{
	for (Widget* widget : m_Widgets)
		widget->processEvent(sfevent);

	return true;
}

void VerticalLayout::add(Widget* widget)
{

	m_Widgets.emplace_back(widget);

	updateShape();
}


/* =========================    HORIZONTAL LAYOUT    ========================= */

void HorizontalLayout::updateShape()
{
	float pos_x = m_Position.x;

	for (Widget* widget : m_Widgets) {
		sf::Vector2f size = widget->getSize();

		widget->setPosition(pos_x, m_Position.y);
		pos_x += size.x + padding;

	}
}

HorizontalLayout::HorizontalLayout(Widget* parent)
	: Layout(2.5f, parent)
{
}

HorizontalLayout::~HorizontalLayout()
{
}

void HorizontalLayout::add(Widget* widget)
{

	m_Widgets.emplace_back(widget);


	updateShape();
}

bool HorizontalLayout::processEvent(const sf::Event& sfevent)
{
	for (Widget* widget : m_Widgets)
		widget->processEvent(sfevent);

	return true;
}
