#pragma once
#include "UI.h"


class State : public sf::Drawable
{
protected:
	std::stack<State*>& m_States;
	sf::RenderWindow& m_Window;

	sf::Vector2f m_MousePosition;

	void updateMousePos();
	typedef std::optional<std::reference_wrapper<Widget>> opt_ref;

public:
	State(sf::RenderWindow& window,std::stack<State*>& states);
	virtual ~State();

	virtual void processEvents(const sf::Event& sfevent) = 0;
	virtual void update(const sf::Time& deltaTime) = 0;

};

