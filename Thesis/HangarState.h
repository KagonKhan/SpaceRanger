#pragma once
#include "State.h"
class HangarState : 
	public State
{
private:
	/* TODO: add proper buttons, sprites, */
	struct CharacterCreation : public sf::Drawable
	{
	private:
		bool m_IsDone;
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override final {
			target.draw(m_AvatarFrame, states);
			target.draw(arrow, states);

			sf::Vector2f pos(m_AvatarFrame.getSize().x- arrow.getSize().x, 0);
			states.transform.translate(pos);
			target.draw(arrow, states);
			
			target.draw(m_TextArea);
			target.draw(doneButton);
		}

		sf::RectangleShape m_AvatarFrame, arrow, m_TextArea, doneButton;
		sf::Sprite m_AvatarSprite;

	public:
		CharacterCreation() 
			: m_IsDone(false)
		{
			m_AvatarFrame.setSize(sf::Vector2f(400, 400));
			m_AvatarFrame.setPosition(sf::Vector2f(300, 300));
			m_AvatarFrame.setFillColor(sf::Color::Cyan);

			arrow.setSize(sf::Vector2f(50, 50));
			arrow.setPosition(m_AvatarFrame.getPosition());
			arrow.setFillColor(sf::Color::Red);


			m_TextArea.setSize(sf::Vector2f(800, 400));
			m_TextArea.setPosition(sf::Vector2f(700, 300));
			m_TextArea.setFillColor(sf::Color::Green);

			doneButton.setSize(sf::Vector2f(75, 30));
			doneButton.setFillColor(sf::Color::Magenta);
			doneButton.setPosition(m_TextArea.getPosition() + m_TextArea.getSize() - sf::Vector2f(75, 30));
		}
		bool getIsDone()const {
			return m_IsDone;
		}

	} m_Creation;
		


	void draw(sf::RenderTarget& target, sf::RenderStates states) const override final;


	sf::Sprite m_Background;




public:
	/* 
		TODO:
			- Some area to spend points,
			- Possibly an area to add modules?
			- Button to launch
			- Some info on current level
			- Ship sprite, enlarged i guess


			- What about levels? A switch with an enum? All of them are classes 
		
	*/
	HangarState(const HangarState&) = delete;
	HangarState operator=(const HangarState&) = delete;

	HangarState(sf::RenderWindow& window, std::stack<State*>& states);

	void processEvents(const sf::Event& sfevent) override final;
	void update(const sf::Time& deltaTime) override final;
};

