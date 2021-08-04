#include "pch.h"
#include "ScrollBarButton.h"

void ScrollBarButton::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_BackgroundRectangle, states);
	target.draw(m_ScrollingButton, states);
}

void ScrollBarButton::processEvent(const sf::Event& sfevent)
{
	bool res = false;
	static bool pressed = false;

	sf::Vector2f mouse_pos(sfevent.mouseMove.x, sfevent.mouseMove.y);



		/* If mouse wheel scrolled, move the button */
	if (sfevent.type == sf::Event::MouseWheelScrolled) {
		if (m_BackgroundRectangle.getGlobalBounds().contains(mouse_pos))
			std::cout << "test\n";
		if (sfevent.mouseWheelScroll.delta > 0)
			m_ScrollingButton.move(2, 0);
		if (sfevent.mouseWheelScroll.delta < 0)
			m_ScrollingButton.move(-2, 0);
	}

		/* If the button pressed, move */
		if (sfevent.type == sf::Event::MouseButtonPressed) {
			m_ScrollingButton.setPosition(mouse_pos);
			pressed = true;
		}
	
	
	if (sfevent.type == sf::Event::MouseButtonReleased)
		pressed = false;


	if (pressed) {
		sf::Vector2f move_pos;
		m_ScrollingButton.setPosition(mouse_pos.x, m_BackgroundRectangle.getPosition().y);
	}

}

void ScrollBarButton::updateMousePosition()
{
	
}

ScrollBarButton::ScrollBarButton(const sf::Vector2f& size, std::string_view text, Widget* parent)
	: Widget(parent), m_Label(text, this)
{
	m_BackgroundRectangle.setSize(size);
	m_ScrollingButton.setSize(sf::Vector2f(25, size.y));

	m_BackgroundRectangle.setFillColor(sf::Color(200, 0, 0, 150));
	m_ScrollingButton.setFillColor(sf::Color::Black);

}

ScrollBarButton::~ScrollBarButton()
{
}

float ScrollBarButton::getValue() const
{
	float bg_pos = m_BackgroundRectangle.getPosition().x;
	float bg_siz = m_BackgroundRectangle.getSize().x;
	float scr_pos = m_ScrollingButton.getPosition().x;

	float value = (scr_pos) / (bg_pos + bg_siz);
	return value;
}

void ScrollBarButton::setPosition(const sf::Vector2f& pos)
{
	m_Position = pos;
	m_BackgroundRectangle.setPosition(m_Position);
	m_ScrollingButton.setPosition(m_Position);
}

void ScrollBarButton::setPosition(float x, float y)
{
	setPosition(sf::Vector2f(x, y));
}

sf::Vector2f ScrollBarButton::getSize() const
{
	return m_BackgroundRectangle.getPosition();
}

void ScrollBarButton::update(const sf::Time& deltaTime)
{
	updateMousePosition();
}
