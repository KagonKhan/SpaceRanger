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


void Layout::setPosition(sf::Vector2f position)
{
	m_Position = position;
	updateShape();
}

void Layout::add(Widget* widget, bool update)
{
	m_Widgets.push_back(widget);

	if(update)
		updateShape();
}

Widget* Layout::getAt(unsigned int index) const
{
	return m_Widgets.at(index);
}

void Layout::update(const sf::Time& deltaTime)
{
}

std::vector<Widget*>& Layout::getWidgets()
{
	return m_Widgets;
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

void VerticalLayout::processEvent(const sf::Event& sfevent)
{
	for (Widget* widget : m_Widgets)
		widget->processEvent(sfevent);

}

sf::Vector2f VerticalLayout::getSize() const
{
	float max_x = 0, curr_y = 0;

	for (Widget* widget : m_Widgets) {
		sf::Vector2f curr_elem_size = widget->getSize();

		if (curr_elem_size.x > max_x)
			max_x = curr_elem_size.x;

		curr_y += curr_elem_size.y + padding;

	}
	return sf::Vector2f(max_x, curr_y);

	
}


/* =========================    SCROLLING LAYOUT    ========================= */

void VerticalScrollingLayout::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_ViewableAreaSprite);

}

void VerticalScrollingLayout::draw()
{
	m_ViewableAreaTexture.clear(sf::Color::Transparent);
	for (Widget* widget : m_Widgets)
		m_ViewableAreaTexture.draw(*widget);

	m_ViewableAreaTexture.display();

	m_ViewableAreaSprite.setTexture(m_ViewableAreaTexture.getTexture());
}

VerticalScrollingLayout::VerticalScrollingLayout(Widget* parent)
	: VerticalLayout(parent), m_MaxScrollSpeed(1000), m_ViewableArea(150, 50, 250, 900), m_CurrentSpeed(0)
{
	m_ViewableAreaTexture.create(600, 500);
}

VerticalScrollingLayout::~VerticalScrollingLayout()
{
}

void VerticalScrollingLayout::processEvent(const sf::Event& sfevent)
{
	for (Widget* widget : m_Widgets)
		widget->processEvent(sfevent);

	if (sfevent.type == sf::Event::MouseWheelScrolled) {
		if (sfevent.mouseWheelScroll.delta > 0)
			m_CurrentSpeed += 100;
		if (sfevent.mouseWheelScroll.delta < 0)
			m_CurrentSpeed -= 100;
	}

}

void VerticalScrollingLayout::update(const sf::Time& deltaTime)
{

	if (m_CurrentSpeed > m_MaxScrollSpeed)
		m_CurrentSpeed = m_MaxScrollSpeed;
	if (m_CurrentSpeed < -m_MaxScrollSpeed)
		m_CurrentSpeed = -m_MaxScrollSpeed;



	sf::Vector2f pos = getPosition();
	sf::Vector2f siz = getSize();

	m_CurrentSpeed *= 0.998;

	//if (pos.y < -10)
	//	pos.y = -10;


	//if (pos.y + (m_CurrentSpeed * deltaTime.asSeconds()) < m_ViewableArea.top && m_CurrentSpeed < 0) {
	//	m_CurrentSpeed *= 0.9;
	//}
	//if (pos.y < m_ViewableArea.top && m_CurrentSpeed > -1) {
	//	m_CurrentSpeed = fabs(m_CurrentSpeed) * 1.03;

	//	if (m_CurrentSpeed < 50)
	//		m_CurrentSpeed = 50;
	//}
	//if (pos.y < m_ViewableArea.top && pos.y > m_ViewableArea.top / 7.f && m_CurrentSpeed > -1) {
	//	m_CurrentSpeed *= 0.90;

	//	if (pos.y + m_CurrentSpeed * deltaTime.asSeconds() > m_ViewableArea.top)
	//		m_CurrentSpeed *= 0.3;
	//}


	setPosition(pos + sf::Vector2f(0, m_CurrentSpeed * deltaTime.asSeconds()));

	draw();
}

/* TODO: fix the mismatch*/
void VerticalScrollingLayout::setViewableArea(const sf::Vector2f& area)
{
	m_ViewableArea = sf::FloatRect(area,area);
}

void VerticalScrollingLayout::setMaxScrollSpeed(float speed)
{
	m_MaxScrollSpeed = speed;
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

void HorizontalLayout::processEvent(const sf::Event& sfevent)
{
	for (Widget* widget : m_Widgets)
		widget->processEvent(sfevent);

}

sf::Vector2f HorizontalLayout::getSize() const
{
	float curr_x = 0, max_y = 0;

	for (Widget* widget : m_Widgets) {
		sf::Vector2f curr_elem_size = widget->getSize();

		if (curr_elem_size.y > max_y)
			max_y = curr_elem_size.y;

		curr_x += curr_elem_size.x + padding;

	}
	return sf::Vector2f(curr_x, max_y);
}

