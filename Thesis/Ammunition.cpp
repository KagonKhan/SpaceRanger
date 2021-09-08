#include "pch.h"
#include "PlayerShip.h"
#include "Ammunition.h"


float perpDot(const sf::Vector2f& A, const sf::Vector2f& B) {
	return (A.x * B.y) - (A.y * B.x);
}
float dot(const sf::Vector2f& A, const sf::Vector2f& B) {
	return (A.x * B.x) + (A.y * B.y);
}





void Ammunition::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_AnimatedSprite);
}

Ammunition::Ammunition(Configuration::TexturesWeaponry tex_id, const sf::Vector2f& boundaries, float deg_angle, float speed, Weapon* parent)
	: Entity(Configuration::textures_weaponry.get(tex_id)), m_DegAngle(deg_angle),m_Speed(speed),
		m_Animation(&Configuration::textures_weaponry.get(tex_id)),
		m_Boundaries(boundaries), m_ShouldBeDeleted(false),
		m_ParentWeapon(parent)
{
	setRadAngle();
}



#pragma region SETTERS / GETTERS


// rotation in degrees
float Ammunition::getRotation() const
{
	return m_RadAngle;
}
float Ammunition::getRotationRad() const
{
	return m_RadAngle;
}

void Ammunition::setRadAngle()
{
	m_RadAngle = m_DegAngle / 180.f * M_PIl;
}


// rotation in degrees, mods the value by 360
void Ammunition::setRotation(float angle)
{
	m_DegAngle = angle;
	m_DegAngle = fmod(m_DegAngle, 360.f);


	/* CAREFUL, 180 deg shift because that's what works for sprites, but for different it might not */
	m_AnimatedSprite.setRotation(m_DegAngle + 180.f);
	m_Sprite.setRotation(m_DegAngle + 180.f);
	setRadAngle();
}
// rotation in degrees, mods the value by 360
void Ammunition::rotate(float angle)
{
	m_DegAngle += angle;
	m_DegAngle = fmod(m_DegAngle, 360.f);


	/* CAREFUL, 180 deg shift because that's what works for sprites, but for different it might not */
	m_AnimatedSprite.setRotation(m_DegAngle + 180.f);
	m_Sprite.setRotation(m_DegAngle + 180.f);
	setRadAngle();
}
// rotation in degrees
float Ammunition::getSpriteRotation() const
{
	return m_Sprite.getRotation();
}
// rotation in degrees
void Ammunition::setSpriteRotation(float angle)
{
	m_Sprite.setRotation(angle);
}
// rotation in degrees
void Ammunition::rotateSprite(float angle)
{
	m_Sprite.rotate(angle);
}

bool Ammunition::getShouldBeDeleted()
{
	return m_ShouldBeDeleted;
}


#pragma endregion



void Ammunition::update(const sf::Time& deltaTime)
{
	updateAnimation(deltaTime);
	updatePosition(deltaTime);
	updateIndividualBehavior(deltaTime);

	if (!Helpers::CheckIfPointContainedInArea(m_Position, Configuration::boundaries))
		m_ShouldBeDeleted = true;
}


void Ammunition::updateAnimation(const sf::Time& deltaTime)
{
	m_AnimatedSprite.update(deltaTime);
}

void Ammunition::updatePosition(const sf::Time& deltaTime)
{
	m_Direction.x = cosf(getRotationRad() + M_PIl / 2.f);
	m_Direction.y = sinf(getRotationRad() + M_PIl / 2.f);
	m_Velocity = m_Direction * m_Speed;

	m_Position += m_Velocity * deltaTime.asSeconds();

	m_AnimatedSprite.setPosition(m_Position);
	m_Sprite.setPosition(m_Position);

}

void Ammunition::setPosition(const sf::Vector2f& pos)
{
	m_Position = pos;
	m_Sprite.setPosition(pos);
	m_AnimatedSprite.setPosition(pos);
}

/* ==============================    LASER    ============================== */

Laser::Laser(Configuration::TexturesWeaponry tex_id, const sf::Vector2f& boundaries, float deg_angle, float speed, Weapon* parent)
	: Ammunition(tex_id, boundaries, deg_angle, speed, parent)
			
{	
	initAnimation();


}

void Laser::initAnimation()
{
	m_Animation.addFramesColumn(1, 3, 0);

	m_AnimatedSprite.setAnimation(&m_Animation);
	m_AnimatedSprite.setFrameTime(sf::seconds(0.2f));
	m_AnimatedSprite.setLoop(false);
	m_AnimatedSprite.setOrigin(m_AnimatedSprite.getSize() / 2.f);
	m_AnimatedSprite.play();
}

void Laser::updateIndividualBehavior(const sf::Time& deltaTime)
{
}

Laser::~Laser()
{

}



/* ==============================    MISSILE    ============================== */




Missile::Missile(Configuration::TexturesWeaponry tex_id, Configuration::TexturesWeaponry thrusters, const sf::Vector2f& boundaries, float deg_angle, float speed, Weapon* parent)
	: Ammunition(thrusters, boundaries, deg_angle, speed, parent),
	m_Target(nullptr), m_RotationRadius(0.5), m_SeekingDistance(400), m_FuelDuration(5.f)
{
	initAnimation();


	m_Sprite.setTexture(Configuration::textures_weaponry.get(tex_id), true);
	m_Sprite.setOrigin(m_Sprite.getGlobalBounds().width / 2.f, m_Sprite.getGlobalBounds().height / 2.f);
	m_Sprite.setScale(0.5f,0.5f);
	m_Sprite.setPosition(m_Position);

}

void Missile::initAnimation()
{

	m_Animation.addFramesLine(16, 1, 0);

	m_AnimatedSprite.setAnimation(&m_Animation);
	m_AnimatedSprite.setOrigin(m_AnimatedSprite.getSize().x / 2.f, 0);
	m_AnimatedSprite.setScale(0.25f, 0.25f);
	m_AnimatedSprite.setFrameTime(sf::seconds(0.1f));
	m_AnimatedSprite.setColor(sf::Color::Yellow);
	m_AnimatedSprite.play();
}

void Missile::updateIndividualBehavior(const sf::Time& deltaTime)
{

	if (m_Target)
		updateTrackingSystem(deltaTime);
}

void Missile::updateTrackingSystem(const sf::Time& deltaTime)
{

	m_FuelDuration -= deltaTime.asSeconds();

	if (m_FuelDuration >= 0) {
		sf::Vector2f tar_pos = m_Target->getPosition();
		sf::Vector2f mis_pos = getPosition();


		if (std::fabsf(tar_pos.x - mis_pos.x) < m_SeekingDistance && std::fabsf(tar_pos.y - mis_pos.y) < m_SeekingDistance) {

			sf::Vector2f A(m_Direction);
			sf::Vector2f B(tar_pos - mis_pos);

			if (perpDot(A, B) < 0) {
				rotate(-m_RotationRadius);
			}
			else if (perpDot(A, B) > 0) {
				rotate(m_RotationRadius);
			}
			else {
				if (dot(A, B) < 0)
					;// missileVelocity.y *= -1;
			}
		}
	}
}

void Missile::draw(sf::RenderTarget& target, sf::RenderStates states) const
{

	target.draw(m_AnimatedSprite);
	target.draw(m_Sprite);
}

void Missile::lockOnTarget(const Entity* target)
{
	m_Target = target;
}


/* ==============================    BEAM    ============================== */



Beam::Beam(Configuration::TexturesWeaponry tex_id, const sf::Vector2f& boundaries, float deg_angle, float speed, Weapon* parent)
	: Ammunition(tex_id, boundaries, deg_angle, speed, parent)
{
	initAnimation();

	m_Speed = 0;
}


void Beam::initAnimation()
{
	m_Animation.addFramesLine(11, 1, 0);

	m_AnimatedSprite.setAnimation(&m_Animation);
	m_AnimatedSprite.setOrigin(sf::Vector2f(m_AnimatedSprite.getSize().x / 2.f, m_AnimatedSprite.getSize().y - 35));
	m_AnimatedSprite.setLoop(false);
	m_AnimatedSprite.setFrameTime(sf::seconds(0.05f));
	m_AnimatedSprite.setRepeat(3);
	m_AnimatedSprite.setScale(1.5f, 4.f);
	m_AnimatedSprite.setRotation(180);
	m_AnimatedSprite.play();
}

void Beam::updateIndividualBehavior(const sf::Time& deltaTime)
{
	if (m_AnimatedSprite.getStatus() != AnimatedSprite::Status::Playing)
		m_ShouldBeDeleted = true;
}