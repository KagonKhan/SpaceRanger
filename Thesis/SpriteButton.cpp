#include "pch.h"
#include "SpriteButton.h"

void SpriteButton::draw(sf::RenderTarget& target, sf::RenderStates) const
{
	target.draw(m_Sprite);
	if (m_Label.has_value())
		target.draw(m_Label.value());
}



SpriteButton::SpriteButton(opt_ref parent, std::optional<sf::Vector2f> size, const sf::Texture& texture)
	: Button(parent), m_Label(std::nullopt), m_Sprite(texture), m_Style(Style::Middle)
{
	if (size.has_value())
		setSize(size.value());
}

SpriteButton::SpriteButton(opt_ref parent, std::optional<sf::Vector2f> size, const sf::Texture& texture, std::string_view text, sf::Font& font, unsigned int charSize)
	: Button(parent), m_Label(std::nullopt), m_Sprite(texture), m_Style(Style::Middle)
{
	m_Label.emplace(opt_ref(*this), text, font, charSize);
	if (size.has_value())
		setSize(size.value());
}

SpriteButton::~SpriteButton()
{
	puts("SpriteButton\t\tdtor");
}



void SpriteButton::processEvent(const sf::Event& sfevent)
{

	if (sfevent.type == sf::Event::MouseButtonPressed && m_Status == Status::Hover)
		m_Status = Status::HoverAndPressed;

	if (sfevent.type == sf::Event::MouseButtonReleased && m_Status == Status::HoverAndPressed && static_cast<sf::Mouse::Button>(sfevent.key.code) == sf::Mouse::Left) {
		if (m_Sprite.getGlobalBounds().contains(static_cast<float>(sfevent.mouseButton.x), static_cast<float>(sfevent.mouseButton.y)))
			on_click(sfevent, *this);
	}
	else if (sfevent.type == sf::Event::MouseMoved) {
		const sf::Vector2f mouse_pos(static_cast<float>(sfevent.mouseMove.x), static_cast<float>(sfevent.mouseMove.y));

		Status old_status = m_Status;
		m_Status = Status::Idle;

		/* If pressed and still hovering, keep pressed */
		if (old_status == Status::HoverAndPressed && m_Sprite.getGlobalBounds().contains(mouse_pos))
			m_Status = Status::HoverAndPressed;
		/* else check if just hovering */
		else if (m_Sprite.getGlobalBounds().contains(mouse_pos))
			m_Status = Status::Hover;
		/* if neither hovering nor pressed = mouse left */
		if ((old_status == Status::Hover || old_status == Status::HoverAndPressed) && !(m_Status == Status::Hover || m_Status == Status::HoverAndPressed))
			onMouseLeft();
		else if (!(old_status == Status::Hover) && (m_Status == Status::Hover))
			onMouseEntered();
	}
}

void SpriteButton::onMouseEntered()
{
	m_Sprite.setColor(sf::Color(182, 182, 182));
	m_Sprite.setColor(sf::Color(182, 182, 182));
}

void SpriteButton::onMouseLeft()
{
	m_Sprite.setColor(sf::Color::White);
}

// Assuming origin is 0,0
void SpriteButton::positionTextBasedOnStyle()
{
	if (!m_Label.has_value())
		return;


	sf::Vector2f pos;
	const sf::Vector2f size(getSize());
	const sf::Vector2f label_size(m_Label.value().getSize());

	switch (m_Style) {
	case Style::TopLeft:
		pos = sf::Vector2f(0, 0);
		break;

	case Style::TopMiddle:
		pos = sf::Vector2f((size.x - label_size.x) / 2.f, 0);
		break;

	case Style::TopRight:
		pos = sf::Vector2f(size.x - label_size.x, 0);
		break;

	case Style::MiddleLeft:
		pos = sf::Vector2f(0, (size.y - label_size.y) / 2.f);
		break;

	case Style::Middle:
		pos = sf::Vector2f((size - label_size) / 2.f);
		break;

	case Style::MiddleRight:
		pos = sf::Vector2f(size.x - label_size.x, (size.y - label_size.y) / 2.f);
		break;

	case Style::BottomLeft:
		pos = sf::Vector2f(0, size.y - label_size.y);
		break;

	case Style::BottomMiddle:
		pos = sf::Vector2f((size.x - label_size.x) / 2.f, size.y - label_size.y);
		break;

	case Style::BottomRight:
		pos = sf::Vector2f(size - label_size);
		break;
	}

	m_Label.value().setPosition(pos + m_Position);
}





#pragma region SETTERS / GETTERS

void SpriteButton::setPosition(const sf::Vector2f& pos)
{
	m_Position = pos;
	m_Sprite.setPosition(m_Position);

	if (m_Label.has_value())
		positionTextBasedOnStyle();
}


sf::Vector2f SpriteButton::getSize() const
{
	return sf::Vector2f(m_Sprite.getGlobalBounds().width, m_Sprite.getGlobalBounds().height);
}


void SpriteButton::setSize(const sf::Vector2f& size)
{
	sf::Vector2f scale(size);
	scale.x /= getSize().x;
	scale.y /= getSize().y;

	m_Sprite.setScale(scale);

	if (m_Label.has_value())
		positionTextBasedOnStyle();
}


void SpriteButton::setStyle(Style style)
{
	if (m_Label.has_value()) {
		m_Style = style;
		positionTextBasedOnStyle();
	}
	else
		throw std::runtime_error("m_Label does not exist!\n");
}


void SpriteButton::setString(const std::string& string)
{
	if (m_Label.has_value()) {
		m_Label.value().setString(string);
		positionTextBasedOnStyle();
	}
	else
		throw std::runtime_error("m_Label does not exist!\n");
}

void SpriteButton::setFont(const sf::Font& font)
{
	if (m_Label.has_value()) {
		m_Label.value().setFont(font);
		positionTextBasedOnStyle();
	}
	else
		throw std::runtime_error("m_Label does not exist!\n");
}

void SpriteButton::setCharacterSize(unsigned int size)
{
	if (m_Label.has_value()) {
		m_Label.value().setCharacterSize(size);
		positionTextBasedOnStyle();
	}
	else
		throw std::runtime_error("m_Label does not exist!\n");
}

void SpriteButton::setLineSpacing(float spacingFactor)
{
	if (m_Label.has_value()) {
		m_Label.value().setLineSpacing(spacingFactor);
		positionTextBasedOnStyle();
	}
	else
		throw std::runtime_error("m_Label does not exist!\n");
}

void SpriteButton::setLetterSpacing(float spacingFactor)
{
	if (m_Label.has_value()) {
		m_Label.value().setLetterSpacing(spacingFactor);
		positionTextBasedOnStyle();
	}
	else
		throw std::runtime_error("m_Label does not exist!\n");
}

void SpriteButton::setTextStyle(sf::Uint32 style)
{
	if (m_Label.has_value()) {
		m_Label.value().setStyle(style);
		positionTextBasedOnStyle();
	}
	else
		throw std::runtime_error("m_Label does not exist!\n");
}

void SpriteButton::setTextFillColor(const sf::Color& color)
{
	if (m_Label.has_value())
		m_Label.value().setFillColor(color);
	else
		throw std::runtime_error("m_Label does not exist!\n");
}

void SpriteButton::setTextOutlineColor(const sf::Color& color)
{
	if (m_Label.has_value())
		m_Label.value().setOutlineColor(color);
	else
		throw std::runtime_error("m_Label does not exist!\n");
}

void SpriteButton::setTextOutlineThickness(float thickness)
{
	if (m_Label.has_value()) {
		m_Label.value().setOutlineThickness(thickness);
		positionTextBasedOnStyle();
	}
	else
		throw std::runtime_error("m_Label does not exist!\n");
}

unsigned int SpriteButton::getCharacterSize() const
{
	if (m_Label.has_value())
		return m_Label.value().getCharacterSize();
	else
		throw std::runtime_error("m_Label does not exist!\n");
}

#pragma endregion