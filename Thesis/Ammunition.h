#pragma once

#include "Entity.h"
#include "CanCollide.h"

# define M_PIl          3.141592653589793238462643383279502884L /* pi */
class Ammunition :
	public Entity,
	public CanCollide
{
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void setRadAngle();

protected:
	float m_Speed;
	float m_DegAngle;
	float m_RadAngle;

public:
	Ammunition(Ammunition&) = delete;
	Ammunition& operator=(Ammunition&) = delete;

	Ammunition(Configuration::Textures tex_id, float deg_angle, float speed);
	
	virtual void update(const sf::Time& deltatime) = 0;

	float getRotation()const;
	float getRotationRad()const;
	void setRotation(float angle);
	void rotate(float angle);
	
	float getSpriteRotation()const;
	void setSpriteRotation(float angle);
	void rotateSprite(float angle);

	
};

#include "AnimatedSprite.h"

class Laser :
	public Ammunition
{
private:
	Animation laserAnimation;
	AnimatedSprite laserSprite;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
public:
	Laser(const Laser&) = delete;
	Laser& operator=(const Laser&) = delete;


	Laser(Configuration::Textures tex_id, float deg_angle, float speed = 400.f);
	virtual ~Laser();


	void setPosition(const sf::Vector2f& pos) override;

	void update(const sf::Time& deltatime);
};

class Rocket :
	public Ammunition
{
private:
	Entity* m_Target;

public:
	Rocket(Rocket&) = delete;
	Rocket& operator=(Rocket&) = delete;


	Rocket(Configuration::Textures tex_id, float deg_angle, float speed = 400.f);

	void lockOnTarget(Entity* target);

	void update(const sf::Time& deltatime);
};

class Beam :
	public Ammunition
{
private:

public:
	Beam(Beam&) = delete;
	Beam& operator=(Beam&) = delete;


	Beam(Configuration::Textures tex_id, float deg_angle, float speed = 400.f);

	void update(const sf::Time& deltatime);
};