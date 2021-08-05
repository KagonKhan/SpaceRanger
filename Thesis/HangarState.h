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
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override final;

		sf::Text m_CharacterDescription;
		sf::String m_CharDescString;
		sf::RectangleShape m_AvatarFrame, m_TextArea, doneButton;
		UI m_UI;
		sf::Sprite m_AvatarSprites[4];
		short int sprite_id;
		Player* m_Player;
		
		
		void initGUI();
		void finishedCreation();
		void swapAvatarSprite(bool left);

	public:
		CharacterCreation(sf::RenderWindow& window, Player* player);
		bool getIsDone()const;
		void processEvents(const sf::Event& sfevent);
	} m_Creation;
		


	void draw(sf::RenderTarget& target, sf::RenderStates states) const override final;
	friend struct CharacterCreation;
	Player* m_Player;
	sf::Sprite m_Background;

	UI m_UI;
	void initUI();

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

