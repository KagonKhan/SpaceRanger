#include "pch.h"
#include "State.h"

void State::updateMousePos()
{
	
}

State::State(sf::RenderWindow& window, std::stack<State::ptr>& states)
	:m_States(states), m_Window(window), m_ShouldQuit(false)
{
	BOOST_LOG_TRIVIAL(info) << "State ctor";
}

State::~State()
{
	BOOST_LOG_TRIVIAL(info) << "State dtor";
}
