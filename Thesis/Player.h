#pragma once
#include "PlayerShip.h"

class HangarState;
class Player : public sf::Drawable
{
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	friend class HangarState;

	sf::Sprite m_Avatar; // TODO some day maybe animated avatar, would be cute
	sf::Vector2f m_Position;

	mutable PlayerShip m_Ship;

	struct Stats {

	public:
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
	} m_PlayerStats;

	PlayerShip& getPlayerShip() const;
	const sf::Sprite& getPlayerShipSprite() const;
	sf::Vector2f getSpriteSize()const;
	void setSpriteScale(const sf::Vector2f& scale);
	Stats& getPlayerStats();


public:
	Player(const Player&) = delete;
	Player& operator=(const Player&) = delete;

	Player(Configuration::TexturesPlayer avatar, const sf::Vector2f& boundaries);
	~Player();

	void setPosition(const sf::Vector2f& pos);


};