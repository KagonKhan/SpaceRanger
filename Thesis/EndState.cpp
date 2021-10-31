#include "pch.h"
#include "EndState.h"

void EndState::draw(sf::RenderTarget& target, sf::RenderStates) const
{
	target.draw(m_Text);
}

EndState::EndState(sf::RenderWindow& window, std::stack<State::ptr>& states)
	: State(window, states)
{
	sf::Vector2f text_size(m_Text.getGlobalBounds().width, m_Text.getGlobalBounds().height);
	m_Text.setPosition((sf::Vector2f(m_Window.getSize()) - text_size) / 2.f);
}

void EndState::update(const sf::Time& deltaTime)
{
	m_ScreenTime += deltaTime.asSeconds(); 

	if (m_ScreenTime > 10.f)
		m_ForceQuit = true;
}

