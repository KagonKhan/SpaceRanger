#pragma once
#include "Entity.h"
#include "ActionTarget.h"
#include "Ship.h"

class Player;
class PlayerShip :
	public Ship
{
private:

	sf::Vector2f m_Boundaries;
	sf::Vector2f m_SpeedLimit;

	bool m_AreActionsBlocked;
	
	Animation m_ExhaustAnimationForward, m_ExhaustAnimationBackward;
	AnimatedSprite m_ExhaustAnimatedSpriteLeft, m_ExhaustAnimatedSpriteRight;

	Player& m_Player;
	

	/* Different types of weapons */
	enum class WeaponType{Laser, Missile, Beam};

	void initVariables();
	void initWeapons();
	void initWeapon(const sf::Vector2f& offset, float firing_rate, WeaponType weapon_type);
	void initAnimations();



	void updateMovement(const sf::Time& deltaTime);
	void updatePosition(const sf::Time& deltaTime);
	void updateSprites(const sf::Time& deltaTime);
	void updateWeapons(const sf::Time& deltaTime);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override final;

public:
	PlayerShip(const PlayerShip&) = delete;
	PlayerShip operator=(const PlayerShip&) = delete;

	PlayerShip(Configuration::TexturesShips tex_id, const sf::Vector2f& boundaries, Player& player);

	void setAreActionsBlocked(bool is_blocked);
	bool getAreActionsBlocked() const;

	void update(const sf::Time& deltaTime);


	const sf::Sprite& getSprite()const;
};

