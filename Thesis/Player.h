#pragma once
#include "PlayerShip.h"

class Player :
	public sf::Drawable
{
private:

friend class PlayerInfoSheet;
friend class HangarState;
	
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	struct Stats {
		int credits;
		short int level;
		short int current_experience;
		short int luck;
		short int level_up_points;

		short int piloting_proficiency;
		short int damage_proficiency;
		short int barter_proficiency;
		short int learning_proficiency;
		//...
		//...
		//...
		//...
	};

	Stats						m_PlayerStats		{ 100, 1, 0, 0, 100,      0,0,0,0 };
	sf::Sprite					m_Avatar; // TODO some day maybe animated avatar, would be cute
	mutable PlayerShip			m_Ship;
	sf::Vector2f				m_Position;






	sf::Vector2f getSpriteSize()const					{			return { m_Avatar.getGlobalBounds().width, m_Avatar.getGlobalBounds().height };			}
	const sf::Sprite& getPlayerShipSprite() const		{			return m_Ship.getSprite();																}
	PlayerShip& getPlayerShip() const					{			return m_Ship;																			}
	Stats& getPlayerStats()								{			return m_PlayerStats;																	}
	void setSpriteScale(const sf::Vector2f& scale)		{			m_Avatar.setScale(scale);																}


public:
	Player(Configuration::TexturesPlayer avatar, const sf::Vector2f& boundaries);

	void setPosition(const sf::Vector2f& pos);


};