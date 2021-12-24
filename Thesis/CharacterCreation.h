#pragma once
#include "SFML/Graphics.hpp"
#include "UI.h"

class HangarState;
class CharacterCreation : 
	public sf::Drawable
{
private:
	void draw(sf::RenderTarget& target, sf::RenderStates) const override;

	sf::RenderWindow&				m_Window;
	HangarState&					m_Hangar;
	std::array<sf::Sprite, 4>		m_AvatarSprites;
	std::array<sf::Text,   4>		m_CharacterDescription;
	std::array<sf::String, 4>		m_CharDescString;
	sf::RectangleShape				m_AvatarFrame;
	sf::RectangleShape				m_TextArea;
	sf::RectangleShape				doneButton;
	UserInterface					m_UI;
	short int						sprite_id;
	bool							m_IsDone{ false };




	void initGUI();
		void addButtonArrows(UnorderedLayout::ptr& unordered_layout);
		void addButtonConfirm(UnorderedLayout::ptr& unordered_layout);

	/// <summary>
	/// Inits the positions for components (avatars, text, buttons)
	/// </summary>
	void initShapes();
	/// <summary>
	/// Loads sprites into the array, and scales them to fit the area
	/// </summary>
	void initAvatars();
	/// <summary>
	/// Sets the descriptions for avatars, formats the text, so that it does not break the container by inserting \n in places.
	/// Does not check if the place is inside a word, resulting in cut words
	/// </summary>
	void initDescriptions();

	/// <summary>
	/// Send the avatar ID to the hangar space, so it can render appropriate one
	/// </summary>
	void finishedCreation();
	/// <summary>
	/// increase
	/// </summary>
	/// <param name="left"></param>
	void swapAvatarSprite(bool left);

public:
	CharacterCreation(sf::RenderWindow& window, HangarState& hangar);


	bool isDone() const;
	/// <summary>
	/// Deals with SFML events
	/// </summary>
	/// <param name="sfevent"></param>
	void processEvents(const sf::Event& sfevent);
};