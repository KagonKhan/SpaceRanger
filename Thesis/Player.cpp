#include "pch.h"
#include "Player.h"

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_Sprite);

	for (Weapon* weapon : m_Weapons)
		target.draw(*weapon);


}


Player::Player(Configuration::Textures avatar_tex_id, const sf::Vector2f& boundaries)
	: Ship(100, Configuration::Textures::PlayerShip), m_Boundaries(boundaries)
{
	m_AvatarSprite.setTexture(Configuration::textures.get(avatar_tex_id));
	initVariables();
	
	m_Weapons.push_back(new LaserTurret(Configuration::Textures::Turret_Laser));
	m_Weapons.back()->setPosition(m_Position);
	m_Weapons.back()->setFiringRate(2);
	m_Weapons.back()->setSpriteRotation(180);
}

void Player::initVariables()
{
	float velocity = 50;
	m_Velocity = sf::Vector2f(velocity * 0.9f, velocity * 0.75f);
	m_Direction = sf::Vector2f(0, 0);
}

void Player::update(const sf::Time& deltaTime)
{
	updateMovement(deltaTime);
	updateSprites(deltaTime);
	updateWeapons(deltaTime);
}

void Player::updateMovement(const sf::Time& deltaTime)
{
	m_Direction *= 0.97f;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		m_Direction.x -= m_Velocity.x;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		m_Direction.x += m_Velocity.x;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		m_Direction.y -= m_Velocity.y;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		m_Direction.y += m_Velocity.y;

#pragma region Movement Boundaries

	// TODO - limit based on sprite size, not based on random nuymbers
	/* Limit movement in X direction, slowly reducing ship velocity */
	if (m_Position.x < 150 && m_Direction.x < 0 || m_Position.x + 150 > m_Boundaries.x && m_Direction.x > 0)
		m_Direction.x *= 0.85f;

	if (m_Position.x < 100 && m_Direction.x < 0 || m_Position.x + 100 > m_Boundaries.x && m_Direction.x > 0)
		m_Direction.x *= 0.65f;

	if (m_Position.x < 50 && m_Direction.x < 0 || m_Position.x + 50 > m_Boundaries.x && m_Direction.x > 0)
		m_Direction.x *= 0.45f;

	if (m_Position.x < 10 && m_Direction.x < 0 || m_Position.x + 10 > m_Boundaries.x && m_Direction.x > 0)
		m_Direction.x *= 0.0f;


	/* Limit movement in Y direction, slowly reducing ship velocity */
	if (m_Position.y > m_Boundaries.y - getSize().y - 10 && m_Direction.y > 0 || m_Position.y < 2.5f * m_Boundaries.y / 4.f + 90.f && m_Direction.y < 0)
		m_Direction.y *= 0.93f;

	if (m_Position.y > m_Boundaries.y - getSize().y + 0 && m_Direction.y > 0 || m_Position.y < 2.5f * m_Boundaries.y / 4.f + 60.f && m_Direction.y < 0)
		m_Direction.y *= 0.75f;

	if (m_Position.y > m_Boundaries.y - getSize().y + 20 && m_Direction.y > 0 || m_Position.y < 2.5f * m_Boundaries.y / 4.f + 30.f && m_Direction.y < 0)
		m_Direction.y *= 0.55f;

	if (m_Position.y > m_Boundaries.y - getSize().y + 40 && m_Direction.y > 0 || m_Position.y < 2.5f * m_Boundaries.y / 4.f + 10.f && m_Direction.y < 0)
		m_Direction.y *= 0.f;

#pragma endregion



	m_Position.x += m_Direction.x * deltaTime.asSeconds();
	m_Position.y += m_Direction.y * deltaTime.asSeconds();

}

void Player::updateSprites(const sf::Time& deltaTime)
{
	m_Sprite.setPosition(m_Position);
	
	for (Weapon* weapon : m_Weapons)
		weapon->setPosition(m_Position);
}

void Player::updateWeapons(const sf::Time& deltaTime)
{
	for (Weapon* weapon : m_Weapons)
		weapon->update(deltaTime);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		shoot();
}
