#pragma once
#include "UI.h"
#include <stack>

class State : public sf::Drawable
{
protected:
	std::stack<State*>& m_States;
	sf::RenderWindow& m_Window;

	sf::Vector2f m_MousePosition;

	void updateMousePos();


public:
	State(sf::RenderWindow& window,std::stack<State*>& states);
	virtual ~State();

	virtual void processEvents(const sf::Event& sfevent) = 0;
	virtual void update(const sf::Time& deltaTime) = 0;

};

