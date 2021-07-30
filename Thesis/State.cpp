#include "pch.h"
#include "State.h"

void State::updateMousePos()
{
	
}

State::State(sf::RenderWindow& window, std::stack<State*>& states)
	:m_Window(window), m_States(states)
{
}

State::~State()
{

}
