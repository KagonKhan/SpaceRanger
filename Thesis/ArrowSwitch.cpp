#include "pch.h"
#include "ArrowSwitch.h"




void ArrowSwitch::draw(sf::RenderTarget& target, sf::RenderStates) const
{
	drawBackground(target);
	drawArrows(target);
	drawCurrentOption(target);
}

void ArrowSwitch::drawBackground(sf::RenderTarget& target) const
{
	target.draw(m_AreaShape);
}

void ArrowSwitch::drawArrows(sf::RenderTarget& target) const
{
	for (auto&& arrow : m_Arrows)
		target.draw(arrow);
}

void ArrowSwitch::drawCurrentOption(sf::RenderTarget& target) const
{
	target.draw(m_Options.get());
}


void ArrowSwitch::processEvent(const sf::Event& sfevent)
{
	processArrowButtonsEvent(sfevent);
}

void ArrowSwitch::processArrowButtonsEvent(const sf::Event& sfevent)
{
	for (auto&& arrow : m_Arrows)
		arrow.processEvent(sfevent);
}



ArrowSwitch::ArrowSwitch(opt_ref parent, unsigned int numberOfOptions, const sf::Vector2f& size, const sf::Texture& left, const sf::Texture& right, std::optional<sf::Vector2f> arrow_size)
	: Widget(parent), m_Padding(5.f), m_Options(numberOfOptions), m_AreaShape(size), m_Arrows{ {opt_ref(*this), arrow_size, left}, {opt_ref(*this), arrow_size, right} }
{


	initColors();

	initButtonFunctionalities();

	reposition();
}

ArrowSwitch::~ArrowSwitch()
{

}

void ArrowSwitch::initColors()
{
	m_FillColor = sf::Color::Transparent;
	m_HoverColor = sf::Color::Transparent;
	m_AreaShape.setFillColor(m_HoverColor);
}

void ArrowSwitch::initButtonFunctionalities()
{
	m_Arrows[0].on_click = [this](const sf::Event&, Button&) {
		m_Options.previous();
	};

	m_Arrows[1].on_click = [this](const sf::Event&, Button&) {
		m_Options.next();
	};
}


void ArrowSwitch::reposition() {
	repositionButtons();
	repositionOptions();
}

void ArrowSwitch::repositionButtons()
{
	const sf::Vector2f area_size(m_AreaShape.getSize());
	const sf::Vector2f arrow_size(m_Arrows[0].getSize());

	// positioned middle vertically
	sf::Vector2f arrow_pos(m_AreaShape.getPosition() + sf::Vector2f(m_Padding, (area_size.y - arrow_size.y) / 2.f));

	m_Arrows[0].setPosition(arrow_pos);

	arrow_pos.x += area_size.x - arrow_size.x - m_Padding;
	m_Arrows[1].setPosition(arrow_pos);
}

void ArrowSwitch::repositionOptions()
{
	const sf::Vector2f pos(m_AreaShape.getPosition());
	const sf::Vector2f area_size(m_AreaShape.getSize());

	// middle
	for (auto&& label : m_Options.getMembers())
		label.setPosition(pos + (area_size - label.getSize()) / 2.f);

}

void ArrowSwitch::addOption(std::string_view option, sf::Font& font, unsigned int charSize)
{
	m_Options.emplace(opt_ref(*this), option, font, charSize);
}

void ArrowSwitch::setPosition(const sf::Vector2f& pos)
{
	m_Position = pos;
	m_AreaShape.setPosition(m_Position);
	reposition();
}

void ArrowSwitch::setSize(const sf::Vector2f& size) {
	m_AreaShape.setSize(size);
	reposition();
}

sf::Vector2f ArrowSwitch::getSize() const
{
	return m_AreaShape.getSize();
}

std::string ArrowSwitch::getString() const
{
	return m_Options.get().getString();
}

