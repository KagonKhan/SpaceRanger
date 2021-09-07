#pragma once
#include "State.h"
#include "Player.h"
#include "CharacterCreation.h"
#include "PlayerInfoSheet.h"
/* Okay this class is really experimental.
	It can be done smarter, and simpler, by having and intermediary character creation state 
		-	(in between main menu and hangar - only if player does not exist)

	Right now it's done fairly poorly, BUT learning cool new features
*/


class HangarState : 
	public State
{
friend class CharacterCreation;
friend class PlayerInfoSheet;
private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override final;

	CharacterCreation m_Creation;

	std::optional<PlayerInfoSheet> m_PlayerInfoArea;

	sf::Sprite m_Background;
	UserInterface m_UI;
	std::optional<Player> m_Player;


	void initGUI();
		void addGUINavigation();
			void addButtonBack(UnoLayPtr& unordered_layout);
			void addButtonNext(UnoLayPtr& unordered_layout);
			void initGUIKeybinds();
	void initBackground();

	
	void onCharacterCreationFinished(int sprite_id);

public:
	/* 
		TODO:
			- Possibly an area to add modules?
			- Some info on current level


			- What about levels? A switch with an enum? All of them are classes 
		
	*/
	HangarState(const HangarState&) = delete;
	HangarState operator=(const HangarState&) = delete;

	HangarState(sf::RenderWindow& window, std::stack<State::ptr>& states);
	virtual ~HangarState();

	void processEvents(const sf::Event& sfevent) override final;
	void update(const sf::Time& deltaTime) override final;
};

