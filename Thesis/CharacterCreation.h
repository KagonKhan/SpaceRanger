#pragma once
#include "SFML/Graphics.hpp"
#include "UI.h"
/* TODO: add proper buttons, sprites, */

class HangarState;
class CharacterCreation : 
	public sf::Drawable
{
private:
	void draw(sf::RenderTarget& target, sf::RenderStates) const override;

	sf::RenderWindow&				m_Window;
	HangarState&					m_Hangar;
	sf::Text						m_CharacterDescription;
	sf::String						m_CharDescString;
	sf::RectangleShape				m_AvatarFrame;
	sf::RectangleShape				m_TextArea;
	sf::RectangleShape				doneButton;
	UserInterface					m_UI;
	std::array<sf::Sprite, 4>		m_AvatarSprites;
	short int						sprite_id;
	bool							m_IsDone{ false };




	void initGUI();
		void addGUINavigation();
			void addButtonArrows(UnorderedLayout::ptr& unordered_layout);
			void addButtonConfirm(UnorderedLayout::ptr& unordered_layout);

	void initAvatars();
	void initShapes();
	void initDescriptions();

	void finishedCreation();
	void swapAvatarSprite(bool left);

public:
	CharacterCreation(sf::RenderWindow& window, HangarState& hangar);


	bool isDone()const;
	void processEvents(const sf::Event& sfevent);
};