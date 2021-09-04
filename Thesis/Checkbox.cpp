#include "pch.h"
#include "Checkbox.h"

#pragma region Cross struct region

void Checkbox::Cross::draw(sf::RenderTarget& target, sf::RenderStates) const
{
	target.draw(m_Shape);
}

Checkbox::Cross::Cross(float size, float thickness, float padding, sf::Color color)
	: m_Shape(sf::Quads, 8), m_Size(size), m_Thickness(thickness), m_Padding(padding)
{
	setPosition(sf::Vector2f(0, 0));
	setColor(color);
	calculateCrossQuads();
}

void Checkbox::Cross::calculateCrossQuads()
{
	float padding = m_Size * m_Padding;
	int a = std::roundf(std::sqrtf(m_Thickness) / 2.f);

	m_Shape[0].position = m_Position + sf::Vector2f(padding, padding) + sf::Vector2f(-a, a);
	m_Shape[1].position = m_Position + sf::Vector2f(m_Size - padding, m_Size - padding) + sf::Vector2f(-a, a);
	m_Shape[2].position = m_Position + sf::Vector2f(m_Size - padding, m_Size - padding) + sf::Vector2f(a, -a);
	m_Shape[3].position = m_Position + sf::Vector2f(padding, padding) + sf::Vector2f(a, -a);

	m_Shape[4].position = m_Position + sf::Vector2f(m_Size - padding, padding) + sf::Vector2f(-a, -a);
	m_Shape[5].position = m_Position + sf::Vector2f(padding, m_Size - padding) + sf::Vector2f(-a, -a);
	m_Shape[6].position = m_Position + sf::Vector2f(padding, m_Size - padding) + sf::Vector2f(a, a);
	m_Shape[7].position = m_Position + sf::Vector2f(m_Size - padding, padding) + sf::Vector2f(a, a);
}



void Checkbox::Cross::setSize(float size)
{
	m_Size = size;
	calculateCrossQuads();
}

void Checkbox::Cross::setPosition(const sf::Vector2f& pos)
{
	m_Position = pos;
	calculateCrossQuads();
}

void Checkbox::Cross::setPosition(float x, float y)
{
	setPosition(sf::Vector2f(x, y));
}

sf::Vector2f Checkbox::Cross::getSize() const
{
	return sf::Vector2f(m_Size, m_Size);
}

void Checkbox::Cross::setColor(const sf::Color& color)
{
	m_Shape[0].color = color;
	m_Shape[1].color = color;
	m_Shape[2].color = color;
	m_Shape[3].color = color;

	m_Shape[4].color = color;
	m_Shape[5].color = color;
	m_Shape[6].color = color;
	m_Shape[7].color = color;
}

void Checkbox::Cross::setPadding(float padding)
{
	if (padding < 0.1)
		padding = 0.1;
	if (padding > 0.9)
		padding = 0.9;
	m_Padding = padding;
	calculateCrossQuads();
}

void Checkbox::Cross::setThickness(float thickness)
{
	m_Thickness = thickness;
	calculateCrossQuads();
}

#pragma endregion













void Checkbox::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_Shape);
	if (m_IsChecked)
		target.draw(m_Cross);
}

Checkbox::Checkbox(float size, const sf::Color& fillColor)
	: m_IsChecked(true), m_Cross(size, 5.f, 0.9f, sf::Color::Black)
{
	setSize(size);
	setPosition(sf::Vector2f(0, 0));
	setFillColor(fillColor);

	setOutlineThickness(1.f);
	m_Shape.setOutlineColor(sf::Color::Black);
}

Checkbox::~Checkbox()
{
}

void Checkbox::setIsChecked(bool checked)
{
	m_IsChecked = checked;
}

bool Checkbox::getIsChecked() const
{
	return m_IsChecked;
}



#pragma region SETTERS / GETTERS

void Checkbox::setPosition(const sf::Vector2f& pos)
{
	m_Position = pos;
	m_Shape.setPosition(m_Position);
	m_Cross.setPosition(m_Position);
}

void Checkbox::setPosition(float x, float y)
{
	setPosition(sf::Vector2f(x, y));
}

void Checkbox::setFillColor(const sf::Color& color)
{
	m_FillColor = color;
	m_Shape.setFillColor(m_FillColor);
}

void Checkbox::setOutlineThickness(float thickness)
{
	m_Shape.setOutlineThickness(thickness);
}

sf::Vector2f Checkbox::getSize() const
{
	return m_Shape.getSize();
}

void Checkbox::setSize(float size)
{
	m_Shape.setSize(sf::Vector2f(size, size));
	m_Cross.setSize(size);
}


#pragma endregion