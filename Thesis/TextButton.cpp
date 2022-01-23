#include "pch.h"
#include "TextButton.h"

void TextButton::draw(sf::RenderTarget& target, sf::RenderStates) const
{
	target.draw(m_Shape);
	target.draw(m_Label);
}


TextButton::TextButton(opt_ref parent, std::optional<sf::Vector2f> size, const sf::Color& fillColor, std::string_view text, sf::Font& font, unsigned int charSize)
	: Button(parent), m_Label(opt_ref(*this), text, font, charSize)
{

	setFillColor(fillColor);

	if (size.has_value())
		m_Shape.setSize(size.value());
	else
		setIsAutoAdjustable(true);
}


void TextButton::processEvent(const sf::Event& sfevent)
{
	if (sfevent.type == sf::Event::MouseButtonPressed && m_Status == Status::Hover)
		m_Status = Status::HoverAndPressed;

	if (sfevent.type == sf::Event::MouseButtonReleased && m_Status == Status::HoverAndPressed && static_cast<sf::Mouse::Button>(sfevent.key.code) == sf::Mouse::Left) {
		if (m_Shape.getGlobalBounds().contains(static_cast<float>(sfevent.mouseButton.x), static_cast<float>(sfevent.mouseButton.y)))
			on_click(sfevent, *this);
	}

	else if (sfevent.type == sf::Event::MouseMoved) {
		const sf::Vector2f mouse_pos(static_cast<float>(sfevent.mouseMove.x), static_cast<float>(sfevent.mouseMove.y));

		Status old_status = m_Status;
		m_Status = Status::Idle;

		/* If pressed and still hovering, keep pressed */
		if (old_status == Status::HoverAndPressed && m_Shape.getGlobalBounds().contains(mouse_pos))
			m_Status = Status::HoverAndPressed;
		/* else check if just hovering */
		else if (m_Shape.getGlobalBounds().contains(mouse_pos))
			m_Status = Status::Hover;
		/* if neither hovering nor pressed = mouse left */
		if ((old_status == Status::Hover || old_status == Status::HoverAndPressed) && !(m_Status == Status::Hover || m_Status == Status::HoverAndPressed))
			onMouseLeft();
		else if (!(old_status == Status::Hover) && (m_Status == Status::Hover))
			onMouseEntered();
	}
}

void TextButton::onMouseEntered()
{
	m_Shape.setFillColor(sf::Color(m_FillColor * sf::Color(182, 182, 182)));
	m_Shape.setOutlineColor(sf::Color(m_OutlineColor * sf::Color(182, 182, 182)));
}

void TextButton::onMouseLeft()
{
	m_Shape.setFillColor(m_FillColor);
	m_Shape.setOutlineColor(m_OutlineColor);
}

// Assuming origin is 0,0
void TextButton::positionTextBasedOnStyle()
{
	sf::Vector2f pos;

	const sf::Vector2f size(getSize());
	const sf::Vector2f label_size(m_Label.getSize());

	switch (m_Style) {
	case Style::TopLeft:		pos = sf::Vector2f(0.f							, 0.f							);		break;
	case Style::TopMiddle:		pos = sf::Vector2f((size.x - label_size.x) / 2.f, 0.f							);		break;
	case Style::TopRight:		pos = sf::Vector2f(size.x - label_size.x		, 0.f							);		break;
	case Style::MiddleLeft:		pos = sf::Vector2f(0.f							, (size.y - label_size.y) / 2.f	);		break;
	case Style::Middle:			pos = sf::Vector2f((size - label_size) / 2.f									);		break;
	case Style::MiddleRight:	pos = sf::Vector2f(size.x - label_size.x		, (size.y - label_size.y) / 2.f	);		break;
	case Style::BottomLeft:		pos = sf::Vector2f(0.f							, size.y - label_size.y			);		break;
	case Style::BottomMiddle:	pos = sf::Vector2f((size.x - label_size.x) / 2.f, size.y - label_size.y			);		break;
	case Style::BottomRight:	pos = sf::Vector2f(size - label_size											);		break;
	default: break;
	}

	m_Label.setPosition(pos + m_Position);
}


void TextButton::adjustSizeToLabel()
{
	sf::Vector2f size(m_Label.getSize());
	size.x += 2.f * static_cast<float>(m_Label.getCharacterSize());
	size.y += 1.5f * static_cast<float>(m_Label.getCharacterSize());

	setSize(size);
	positionTextBasedOnStyle();
}



#pragma region SETTERS / GETTERS


void TextButton::setPosition(const sf::Vector2f& pos)
{
	m_Position = pos;
	m_Shape.setPosition(m_Position);

	positionTextBasedOnStyle();
}

void TextButton::setOutlineThickness(float thickness)
{
	m_Shape.setOutlineThickness(thickness);
}

void TextButton::setOutlineColor(const sf::Color& color)
{
	m_Shape.setOutlineColor(color);
}

void TextButton::setFillColor(const sf::Color& color)
{
	m_FillColor = color;
	m_Shape.setFillColor(m_FillColor);
}

void TextButton::setStyle(Style style)
{
	m_Style = style;
	positionTextBasedOnStyle();
}

void TextButton::setIsAutoAdjustable(bool adjust)
{
	m_IsAutoAdjustable = adjust;
	adjustSizeToLabel();
	
}

void TextButton::setSize(const sf::Vector2f& size)
{
	m_Shape.setSize(size);
	positionTextBasedOnStyle();
}





/* TEXT SETTERS */
void TextButton::setString(const std::string& string)
{
	m_Label.setString(string);

	if (m_IsAutoAdjustable)
		adjustSizeToLabel();
}

void TextButton::setFont(const sf::Font& font)
{
	m_Label.setFont(font);
	if (m_IsAutoAdjustable)
		adjustSizeToLabel();
}

void TextButton::setCharacterSize(unsigned int size)
{
	m_Label.setCharacterSize(size);
	if (m_IsAutoAdjustable)
		adjustSizeToLabel();
}

void TextButton::setLineSpacing(float spacingFactor)
{
	m_Label.setLineSpacing(spacingFactor);
	if (m_IsAutoAdjustable)
		adjustSizeToLabel();
}

void TextButton::setLetterSpacing(float spacingFactor)
{
	m_Label.setLetterSpacing(spacingFactor);
	if (m_IsAutoAdjustable)
		adjustSizeToLabel();
}

void TextButton::setTextStyle(sf::Uint32 style)
{
	m_Label.setStyle(style);
	if (m_IsAutoAdjustable)
		adjustSizeToLabel();
}

void TextButton::setTextOutlineThickness(float thickness)
{
	m_Label.setOutlineThickness(thickness);
	if (m_IsAutoAdjustable)
		adjustSizeToLabel();
}


#pragma endregion