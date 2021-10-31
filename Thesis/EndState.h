#pragma once
#include "State.h"


class EndState :
	public State
{
private:
	void draw(sf::RenderTarget& target, sf::RenderStates) const override;

	sf::Text m_Text{ "That's all (for now) folks!", Configuration::fonts.get(Configuration::Fonts::SpaceGui), 90U };

	float m_ScreenTime{ 0.f };

public:
	EndState(sf::RenderWindow& window, std::stack<State::ptr>& states);


	void processEvents(const sf::Event& sfevent) override {};
	void update(const sf::Time& deltaTime) override;
};