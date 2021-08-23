#include "pch.h"

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

Ammunition::Ammunition(Configuration::Textures tex_id, const sf::Vector2f& boundaries, float deg_angle, float speed)
	: Entity(tex_id), m_DegAngle(deg_angle),m_Speed(speed),
		m_Animation(&Configuration::textures.get(tex_id)),
		m_Boundaries(boundaries), m_ShouldBeDeleted(false)
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
	setRadAngle();
}
// rotation in degrees, mods the value by 360
void Ammunition::rotate(float angle)
{
	m_DegAngle += angle;
	m_DegAngle = fmod(m_DegAngle, 360.f);


	/* CAREFUL, 180 deg shift because that's what works for sprites, but for different it might not */
	m_AnimatedSprite.setRotation(m_DegAngle + 180.f);

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

	if (!Configuration::CheckIfPointContainedInArea(m_Position, Configuration::boundaries))
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


	m_AnimatedSprite.move(m_Velocity * deltaTime.asSeconds());
	m_Position = m_AnimatedSprite.getPosition();

}

void Ammunition::setPosition(const sf::Vector2f& pos)
{
	m_Position = pos;
	m_AnimatedSprite.setPosition(pos);
}

/* ==============================    LASER    ============================== */

Laser::Laser(Configuration::Textures tex_id, const sf::Vector2f& boundaries, float deg_angle, float speed)
	: Ammunition(tex_id, boundaries, deg_angle, speed)
			
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



/* ==============================    ROCKET    ============================== */




Missile::Missile(Configuration::Textures tex_id, const sf::Vector2f& boundaries, float deg_angle, float speed)
	: Ammunition(tex_id, boundaries, deg_angle, speed), m_Target(nullptr)
{
	initAnimation();
	/*
		TO DO; 
			- Animated rocket? exhaust?
	
	*/
}

void Missile::initAnimation()
{
	m_Animation.addFramesColumn(1, 1, 0);

	m_AnimatedSprite.setAnimation(&m_Animation);
	m_AnimatedSprite.setOrigin(m_AnimatedSprite.getSize() / 2.f);
	m_AnimatedSprite.setLoop(false);

	m_AnimatedSprite.setScale(0.5f, 0.5f);
	//m_AnimatedSprite.play();
}

void Missile::updateIndividualBehavior(const sf::Time& deltaTime)
{

	sf::Vector2f A(m_Direction);
	sf::Vector2f B(Configuration::tar.getPosition() - getPosition());

	if (perpDot(A, B) < 0) {
		rotate(-2.f);
	}
	else if (perpDot(A, B) > 0) {
		rotate(2.f);
	}
	else {
		if (dot(A, B) < 0)
			;// missileVelocity.y *= -1;
	}

}

void Missile::lockOnTarget(Entity* target)
{
	m_Target = target;
}


/* ==============================    BEAM    ============================== */



Beam::Beam(Configuration::Textures tex_id, const sf::Vector2f& boundaries, float deg_angle, float speed)
	:Ammunition(tex_id, boundaries, deg_angle, speed)
{
	initAnimation();
}


void Beam::initAnimation()
{
}

void Beam::updateIndividualBehavior(const sf::Time& deltaTime)
{
}