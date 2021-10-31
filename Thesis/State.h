#pragma once
#include "UI.h"


class State :
	public sf::Drawable
{
protected:
	std::stack<std::unique_ptr<State>>&			m_States;
	sf::RenderWindow&							m_Window;
	sf::Vector2f								m_MousePosition;
	bool										m_ShouldQuit		{ false };
	bool										m_ForceQuit			{ false };


	using opt_ref = std::optional<std::reference_wrapper<Widget>>;

	void updateMousePos();


public:
	using ptr = std::unique_ptr<State>;

	State(sf::RenderWindow& window,std::stack<State::ptr>& states);
	~State() override;

	virtual void processEvents(const sf::Event& sfevent) = 0;
	virtual void update(const sf::Time& deltaTime) = 0;

	bool forcedQuit() const { return m_ForceQuit; };
};

