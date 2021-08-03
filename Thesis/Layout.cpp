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

void Layout::add(Widget* widget)
{
	m_Widgets.push_back(widget);

	updateShape();
}

Widget* Layout::getAt(unsigned int index) const
{
	return m_Widgets.at(index);
}

void Layout::update(const sf::Time& deltaTime)
{
}

void Layout::hideAllButtons()
{
	/* TODO: clean up this */
	for (Widget* widget : m_Widgets) {
		dynamic_cast<Button*>(widget)->setIsVisible(false);
		dynamic_cast<Button*>(widget)->setIsActive(false);

	}
}

void Layout::showAllButtons()
{
	/* TODO: clean up this */
	for (Widget* widget : m_Widgets)
		if(typeid(*widget).name() == typeid(TextButton).name())
			dynamic_cast<TextButton*>(widget)->setIsVisible(true);
}

void Layout::setAllButtonsStatus(bool status)
{
	/* TODO: expand this, right now it does random stuff, and it's confusing*/
	for (Widget* widget : m_Widgets) {
		if (typeid(*widget).name() == typeid(Checkbox).name()) {
			dynamic_cast<Checkbox*>(widget)->setChecked(status);
		}
		else if (typeid(*widget).name() == typeid(TextButton).name()) {
			dynamic_cast<TextButton*>(widget)->setIsActive(false);

		}

	}
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

bool VerticalScrollingLayout::processEvent(const sf::Event& sfevent)
{
	for (Widget* widget : m_Widgets)
		widget->processEvent(sfevent);

	if (sfevent.type == sf::Event::MouseWheelScrolled) {
		if (sfevent.mouseWheelScroll.delta > 0)
			m_CurrentSpeed += 100;
		if (sfevent.mouseWheelScroll.delta < 0)
			m_CurrentSpeed -= 100;
	}

	return true;
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

bool HorizontalLayout::processEvent(const sf::Event& sfevent)
{
	for (Widget* widget : m_Widgets)
		widget->processEvent(sfevent);

	return true;
}

