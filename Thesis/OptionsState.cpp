#include "OptionsState.h"

void OptionsState::initGUI()
{
}

void OptionsState::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
}

void OptionsState::Options()
{
}

void OptionsState::NewGame()
{
}

void OptionsState::processEvents(const sf::Event& sfevent)
{
}

OptionsState::OptionsState(sf::RenderWindow& window, std::stack<State*>& states)
	: State(window, states), ui(window)
{
}

OptionsState::~OptionsState()
{
}

void OptionsState::update(const sf::Time& deltaTime)
{
}
