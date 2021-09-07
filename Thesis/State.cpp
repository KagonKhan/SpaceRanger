#include "pch.h"
#include "State.h"

void State::updateMousePos()
{
	
}

State::State(sf::RenderWindow& window, std::stack<State::ptr>& states)
	:m_Window(window), m_States(states), m_ShouldQuit(false)
{
	puts("State\t\tctor");
}

State::~State()
{
	puts("State\t\tdtor");
}
