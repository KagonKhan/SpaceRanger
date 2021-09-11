#pragma once
#include "SFML/Graphics.hpp"
#include "UI.h"
/* TODO: add proper buttons, sprites, */

class HangarState;
class CharacterCreation : 
	public sf::Drawable
{
private:
	void draw(sf::RenderTarget& target, sf::RenderStates) const override final;
	bool m_IsDone;

	sf::Text m_CharacterDescription;
	sf::String m_CharDescString;
	sf::RectangleShape m_AvatarFrame, m_TextArea, doneButton;

	UserInterface m_UI;
	sf::Sprite m_AvatarSprites[4];
	short int sprite_id;

	sf::RenderWindow& m_Window;
	HangarState& m_Hangar;


	void initGUI();
		void addGUINavigation();
			void addButtonArrows(UnoLayPtr& unordered_layout);
			void addButtonConfirm(UnoLayPtr& unordered_layout);

	void initAvatars();
	void initShapes();
	void initDescriptions();

	void finishedCreation();
	void swapAvatarSprite(bool left);

public:
	CharacterCreation(sf::RenderWindow& window, HangarState& hangar);
	~CharacterCreation();

	bool isDone()const;
	void processEvents(const sf::Event& sfevent);
};