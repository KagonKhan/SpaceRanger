#include "pch.h"

#include "Ammunition.h"


void Ammunition::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_AnimatedSprite);
}

void Ammunition::setRadAngle()
{
	m_RadAngle = m_DegAngle / 180.f * M_PIl;
}

Ammunition::Ammunition(Configuration::Textures tex_id, const sf::Vector2f& boundaries, float deg_angle, float speed)
	:Entity(tex_id), m_DegAngle(deg_angle),m_Speed(speed),
		m_Animation(&Configuration::textures.get(tex_id)),
		m_Boundaries(boundaries), m_ShouldBeDeleted(false)
{


	setRadAngle();
	/* CAREFUL, Sprite angle 0 might point upwards, but here assumed 0 is pointing right */
	m_Direction.x = cosf(getRotationRad());
	m_Direction.y = sinf(getRotationRad());

	m_Velocity = m_Direction * m_Speed;




}
// rotation in degrees
float Ammunition::getRotation() const
{
	return m_RadAngle;
}
float Ammunition::getRotationRad() const
{
	return m_RadAngle;
}
// rotation in degrees, mods the value by 360
void Ammunition::setRotation(float angle)
{
	m_DegAngle = angle;
	m_DegAngle = fmod(m_DegAngle, 360.f);

	setRadAngle();
}
// rotation in degrees, mods the value by 360
void Ammunition::rotate(float angle)
{
	m_DegAngle += angle;
	m_DegAngle = fmod(m_DegAngle, 360.f);

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




void Ammunition::updateAnimation(const sf::Time& deltaTime)
{
	m_AnimatedSprite.update(deltaTime);
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

	m_Animation.addFramesColumn(1, 3, 0);

	m_AnimatedSprite.setAnimation(&m_Animation);
	m_AnimatedSprite.setFrameTime(sf::seconds(0.2f));
	m_AnimatedSprite.setLoop(false);
	m_AnimatedSprite.setOrigin(m_AnimatedSprite.getSize() / 2.f);
	m_AnimatedSprite.play();


}

Laser::~Laser()
{

}


void Laser::update(const sf::Time& deltaTime)
{
	updateAnimation(deltaTime);

	if (!Configuration::CheckIfPointContainedInArea(m_Position, Configuration::boundaries))
		m_ShouldBeDeleted = true;
}





/* ==============================    ROCKET    ============================== */






Missile::Missile(Configuration::Textures tex_id, const sf::Vector2f& boundaries, float deg_angle, float speed)
	: Ammunition(tex_id, boundaries, deg_angle, speed), m_Target(nullptr)
{

	m_Animation.addFramesColumn(1, 1, 0);

	m_AnimatedSprite.setAnimation(&m_Animation);
	m_AnimatedSprite.setOrigin(m_AnimatedSprite.getSize() / 2.f);
	m_AnimatedSprite.setLoop(false);

	m_AnimatedSprite.setScale(0.5f, 0.5f);
	//m_AnimatedSprite.play();






	/*
		TO DO; 
			- Animated rocket? exhaust?
	
	*/
}

void Missile::lockOnTarget(Entity* target)
{
	m_Target = target;
}

void Missile::update(const sf::Time& deltaTime)
{

	updateAnimation(deltaTime);

	if (!Configuration::CheckIfPointContainedInArea(m_Position, Configuration::boundaries))
		m_ShouldBeDeleted = true;
}



/* ==============================    BEAM    ============================== */



Beam::Beam(Configuration::Textures tex_id, const sf::Vector2f& boundaries, float deg_angle, float speed)
	:Ammunition(tex_id, boundaries, deg_angle, speed)
{
}

void Beam::update(const sf::Time& deltaTime)
{
	/* TODO animation update*/
}
