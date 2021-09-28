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
	void draw(sf::RenderTarget& target, sf::RenderStates) const override;


	CharacterCreation						m_Creation;
	std::optional<PlayerInfoSheet>			m_PlayerInfoArea	{ std::nullopt };
	std::optional<Player>					m_Player			{ std::nullopt };
	sf::Sprite								m_Background		{ Configuration::textures_hangar.get(Configuration::TexturesHangarState::background) };
	UserInterface							m_UI;



	void initGUI();
		void addGUINavigation();
			void addButtonBack(UnorderedLayout::ptr& unordered_layout);
			void addButtonNext(UnorderedLayout::ptr& unordered_layout);
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
	HangarState(sf::RenderWindow& window, std::stack<State::ptr>& states);


	void processEvents(const sf::Event& sfevent) override ;
	void update(const sf::Time& deltaTime) override ;
};

