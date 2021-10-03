#include "pch.h"
#include "PlayerShip.h"
#include "Weaponry.h"

void PlayerShip::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (auto&& weapon : m_Weapons)
		target.draw(*weapon);

	target.draw(m_Sprite);
	target.draw(m_ExhaustAnimatedSpriteLeft);
	target.draw(m_ExhaustAnimatedSpriteRight);
}

PlayerShip::PlayerShip(Configuration::TexturesShips tex_id, const sf::Vector2f& boundaries, Player& player)
	: Ship(100, tex_id), m_Boundaries(boundaries)
	//m_Player(player),
{
	initVariables();
	initWeapons();
	initAnimations();
	
}

PlayerShip::PlayerShip(Configuration::TexturesShips tex_id, const sf::Vector2f& boundaries)
	: Ship(100, tex_id), m_Boundaries(boundaries)
{
	initVariables();
	initWeapons();
	initAnimations();
}



#pragma region Initializers / Setters / Getters

void PlayerShip::initVariables() 
{
	m_Speed = 300.f;
}

void PlayerShip::initWeapons()
{
	addWeapon(m_Position, sf::Vector2f( 60.f, 0.f),  .25f, WeaponType::Missile);
	addWeapon(m_Position, sf::Vector2f(-60.f, 0.f),  .25f, WeaponType::Missile);
	addWeapon(m_Position, sf::Vector2f(-20.f, 0.f),  10.f, WeaponType::Laser);
	addWeapon(m_Position, sf::Vector2f( 20.f, 0.f),  10.f, WeaponType::Laser);
	addWeapon(m_Position, sf::Vector2f(-20.f, 0.f),  10.f, WeaponType::Laser);
	addWeapon(m_Position, sf::Vector2f( 20.f, 0.f),  10.f, WeaponType::Laser);
	addWeapon(m_Position, sf::Vector2f( 0 ,-10.f),   0.0005f, WeaponType::Beam, 180.f, Entity::opt_ref(*this));
}


void PlayerShip::initAnimations()
{
	Animation::Line framesForward{ 8,1,0,0,3 };
	Animation::Line framesBackward{ 8,1,0,5,0 };
	m_ExhaustAnimationForward.addFrames(framesForward);
	m_ExhaustAnimationBackward.addFrames(framesBackward);


	m_ExhaustAnimatedSpriteLeft.setAnimation(&m_ExhaustAnimationForward);
	m_ExhaustAnimatedSpriteLeft.setLoop(false);
	m_ExhaustAnimatedSpriteLeft.setRepeat(0);
	m_ExhaustAnimatedSpriteLeft.setOrigin(m_ExhaustAnimatedSpriteLeft.getSize().x / 2.f, 0);
	m_ExhaustAnimatedSpriteLeft.setPosition(m_Position);
	m_ExhaustAnimatedSpriteLeft.setOffset(sf::Vector2f(-23.f, 32.f));
	m_ExhaustAnimatedSpriteLeft.setFrame(1);
	m_ExhaustAnimatedSpriteLeft.setScale(1.f, 0.9f);


	m_ExhaustAnimatedSpriteRight = m_ExhaustAnimatedSpriteLeft;
	m_ExhaustAnimatedSpriteRight.setOffset(sf::Vector2f(23.f, 32.f));
}

#pragma endregion



void PlayerShip::updateMovement(const sf::Time& deltaTime)
{
	m_Direction *= 0.97f;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))				m_Direction.x -= m_Speed;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))				m_Direction.x += m_Speed;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))				m_Direction.y -= m_Speed;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))				m_Direction.y += m_Speed;

	checkBoundaries();
	checkMaxSpeed();



	move(m_Direction * deltaTime.asSeconds());

	sf::Listener::setPosition(m_Position.x, -m_Position.y, 300.f);
}

void PlayerShip::checkBoundaries()
{	
	if (m_Position.x < 150 && m_Direction.x < 0 || m_Position.x + 150 > m_Boundaries.x && m_Direction.x > 0)		m_Direction.x *= 0.85f;
	if (m_Position.x < 100 && m_Direction.x < 0 || m_Position.x + 100 > m_Boundaries.x && m_Direction.x > 0)		m_Direction.x *= 0.65f;
	if (m_Position.x < 50  && m_Direction.x < 0 || m_Position.x + 50  > m_Boundaries.x && m_Direction.x > 0)		m_Direction.x *= 0.45f;
	if (m_Position.x < 10  && m_Direction.x < 0 || m_Position.x + 10  > m_Boundaries.x && m_Direction.x > 0)		m_Direction.x *= 0.0f;

	if (m_Position.y > m_Boundaries.y - getSize().y - 10 && m_Direction.y > 0 || m_Position.y < 2.5f * m_Boundaries.y / 4.f + 90.f && m_Direction.y < 0)		m_Direction.y *= 0.93f;
	if (m_Position.y > m_Boundaries.y - getSize().y + 0  && m_Direction.y > 0 || m_Position.y < 2.5f * m_Boundaries.y / 4.f + 60.f && m_Direction.y < 0)		m_Direction.y *= 0.75f;
	if (m_Position.y > m_Boundaries.y - getSize().y + 20 && m_Direction.y > 0 || m_Position.y < 2.5f * m_Boundaries.y / 4.f + 30.f && m_Direction.y < 0)		m_Direction.y *= 0.55f;
	if (m_Position.y > m_Boundaries.y - getSize().y + 40 && m_Direction.y > 0 || m_Position.y < 2.5f * m_Boundaries.y / 4.f + 10.f && m_Direction.y < 0)		m_Direction.y *= 0.f;
}


void PlayerShip::checkMaxSpeed()
{	
	if		(m_Direction.x > m_SpeedLimit.x)		m_Direction.x = m_SpeedLimit.x;
	else if (m_Direction.x < -m_SpeedLimit.x)		m_Direction.x = -m_SpeedLimit.x;
	else if (m_Direction.y > m_SpeedLimit.y)		m_Direction.y = m_SpeedLimit.y;
	else if (m_Direction.y < -m_SpeedLimit.y)		m_Direction.y = -m_SpeedLimit.y;



	if (float len = Helpers::getLength(m_Direction); m_SpeedLimit.x < len) {
		len = m_SpeedLimit.x / len;
		m_Direction *= len;
	}


}

void PlayerShip::updateIndividualBehavior(const sf::Time& deltaTime)
{
	updateSprites(deltaTime);



	if (!m_AreActionsBlocked && sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		shoot();
}

void PlayerShip::updateSprites(const sf::Time& deltaTime)
{
	// if moving up, swap animation to stronger exhaust
	if (m_Direction.y > 0) {
		m_ExhaustAnimatedSpriteLeft.setAnimation(&m_ExhaustAnimationForward);
		m_ExhaustAnimatedSpriteRight.setAnimation(&m_ExhaustAnimationForward);
	}
	// if moving down, swap animation to weaker exhaust
	else if (m_Direction.y < 0) {
		m_ExhaustAnimatedSpriteLeft.setAnimation(&m_ExhaustAnimationBackward);
		m_ExhaustAnimatedSpriteRight.setAnimation(&m_ExhaustAnimationBackward);
	}

	m_ExhaustAnimatedSpriteLeft.update(deltaTime);
	m_ExhaustAnimatedSpriteRight.update(deltaTime);

	m_ExhaustAnimatedSpriteLeft.setPosition(m_Position);
	m_ExhaustAnimatedSpriteRight.setPosition(m_Position);
}
