#pragma once
#include "Entity.h"
#include "ActionTarget.h"
#include "Ship.h"

class Player;
class PlayerShip :
	public Ship
{
private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const final;

	sf::Vector2f		m_Boundaries;
	sf::Vector2f		m_SpeedLimit					{		1200, 900		};
	Animation			m_ExhaustAnimationForward		{		&Configuration::textures_ships.get(Configuration::TexturesShips::player_exhaust)		};
	Animation			m_ExhaustAnimationBackward		{		&Configuration::textures_ships.get(Configuration::TexturesShips::player_exhaust)		};
	AnimatedSprite		m_ExhaustAnimatedSpriteLeft;
	AnimatedSprite		m_ExhaustAnimatedSpriteRight;



	//Player& m_Player;

	void initVariables();
	void initWeapons();
	void initAnimations();

	void updateMovement(const sf::Time& deltaTime) override;
	void checkBoundaries();
	void checkMaxSpeed();
	void updateSprites(const sf::Time& deltaTime);
	void updateIndividualBehavior(const sf::Time& deltaTime) override;

	void onDestroy() override;

public:
	PlayerShip(Configuration::TexturesShips tex_id, const sf::Vector2f& boundaries, Player& player);
	PlayerShip(Configuration::TexturesShips tex_id, const sf::Vector2f& boundaries);

};

