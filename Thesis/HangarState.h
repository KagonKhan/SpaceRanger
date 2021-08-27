#pragma once
#include "State.h"

#include "Player.h"

/* Okay this class is really experimental.
	It can be done smarter, and simpler, by having and intermediary character creation state 
		-	(in between main menu and hangar - only if player does not exist)

	Right now it's done fairly poorly, BUT learning cool new features
*/


class HangarState : 
	public State
{
private:

#pragma region Character Creation
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

		sf::RenderWindow& m_Window;
		HangarState& m_Hangar;


		void initGUI();
		void initAvatars();
		void initShapes();
		void initDescriptions();

		void finishedCreation();
		void swapAvatarSprite(bool left);

	public:
		CharacterCreation(sf::RenderWindow& window, HangarState& hangar);
		~CharacterCreation();
		bool getIsDone()const;
		void processEvents(const sf::Event& sfevent);
	};
	void drawCharacterCreation(sf::RenderTarget& target, sf::RenderStates states) const;
	void processEventsCharacterCreation(const sf::Event& sfevent);


	std::unique_ptr<CharacterCreation> m_Creation;
	friend struct CharacterCreation;

	void onCharacterCreationFinished(int sprite_id);
#pragma endregion



#pragma region Player Info Area


	struct PlayerInfoArea : public sf::Drawable
	{
	private:
		/*
			Exp bar, level, points, level, maybe some time shop, weapon parts that you can drag?
			different ships
		*/
		enum RectangleShapesIDs{ m_PlayerArea, m_PlayerAreaTop, m_PlayerAvatar, m_PlayerAreaBottom, m_ShipArea, m_ExpBarBackground, m_ExpBar, COUNT};

		sf::RectangleShape m_RectangleShapes[static_cast<unsigned int>(RectangleShapesIDs::COUNT)];

		sf::RenderWindow& m_Window;
		HangarState& m_Hangar;
		std::optional<Player>& m_Player;
		
		UI m_UI;
		sf::Sprite m_ShipSprite;


		void draw(sf::RenderTarget& target, sf::RenderStates states) const override final;
		void initGUI();

	public:
		PlayerInfoArea(sf::RenderWindow& window, HangarState& hangar, std::optional<Player>& player);
		~PlayerInfoArea();


		void processEvents(const sf::Event& sfevent);
	};

	std::optional<PlayerInfoArea> m_PlayerInfoArea;

#pragma endregion





	void draw(sf::RenderTarget& target, sf::RenderStates states) const override final;
	
	sf::Sprite m_Background;

	UI m_UI;

	std::optional<Player> m_Player;


	void initGUI();
	void initBackground();

	

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

