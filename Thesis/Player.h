#pragma once
#include "Entity.h"
#include "ActionTarget.h"
#include "Ship.h"

class Player :
	public Ship
{
private:
	sf::Sprite m_AvatarSprite;
	sf::Vector2f m_Boundaries;
	
	bool m_AreActionsBlocked;
	
	/* Different types of weapons */
	
	void initVariables();

	void updateMovement(const sf::Time& deltaTime);
	void updateSprites(const sf::Time& deltaTime);
	void updateWeapons(const sf::Time& deltaTime);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override final;

public:
	Player(const Player&) = delete;
	Player operator=(const Player&) = delete;

	Player(Configuration::Textures tex_id, const sf::Vector2f& boundaries);

	void setAreActionsBlocked(bool is_blocked);

	void update(const sf::Time& deltaTime);
};

