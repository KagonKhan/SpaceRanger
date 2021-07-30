#include "pch.h"
#include "Action.h"

Action::Action(const sf::Keyboard::Key& key, int type)
	: m_Type(type)
{
	m_Event.type = sf::Event::EventType::KeyPressed;
	m_Event.key.code = key;
}

Action::Action(const sf::Mouse::Button& key, int type)
	: m_Type(type)
{
	m_Event.type = sf::Event::EventType::MouseButtonPressed;
	m_Event.mouseButton.button = key;
}

Action::Action(const Action& other)
	: m_Type(other.m_Type)
{
	std::memcpy(&m_Event, &other.m_Event, sizeof(sf::Event));
}

Action& Action::operator=(const Action& other)
{
	std::memcpy(&m_Event, &other.m_Event, sizeof(sf::Event));
	m_Type = other.m_Type;
	return *this;
}

bool Action::test() const
{
	bool result = false;

	if (m_Event.type == sf::Event::EventType::KeyPressed)
		if (m_Type == Type::Pressed)
			result = sf::Keyboard::isKeyPressed(m_Event.key.code);
	
	if (m_Event.type == sf::Event::EventType::MouseButtonPressed)
		if (m_Type == Type::Pressed)
			result = sf::Mouse::isButtonPressed(m_Event.mouseButton.button);


	return result;
}

bool Action::operator==(const Action& other) const
{
	return m_Type == other.m_Type && other == m_Event;
}

bool Action::operator==(const sf::Event& sfEvent) const
{
	bool result = false;

	switch (sfEvent.type) {
		case sf::Event::EventType::KeyPressed:
			if (m_Type & Type::Pressed && m_Event.type == sf::Event::EventType::KeyPressed)
				result = sfEvent.key.code == m_Event.key.code;
		break;

		case sf::Event::EventType::KeyReleased:
			if (m_Type & Type::Released && m_Event.type == sf::Event::EventType::KeyPressed)
				result = sfEvent.key.code == m_Event.key.code;
		break;

		case sf::Event::EventType::MouseButtonPressed:
			if (m_Type & Type::Pressed && m_Event.type == sf::Event::EventType::MouseButtonPressed)
				result = sfEvent.mouseButton.button == m_Event.mouseButton.button;
		break;

		case sf::Event::EventType::MouseButtonReleased:
			if (m_Type & Type::Pressed && m_Event.type == sf::Event::EventType::MouseButtonPressed)
				result = sfEvent.mouseButton.button == m_Event.mouseButton.button;
		break;

		default:
			break;
	}

	return result;
}
