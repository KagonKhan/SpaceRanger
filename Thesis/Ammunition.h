#pragma once

#include "Entity.h"
#include "CanCollide.h"

#include "AnimatedSprite.h"

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
	bool m_ShouldBeDeleted;


	sf::Vector2f m_Boundaries;

	Animation m_Animation;
	AnimatedSprite m_AnimatedSprite;

	void updateAnimation(const sf::Time& deltaTime);

public:
	Ammunition(Ammunition&) = delete;
	Ammunition& operator=(Ammunition&) = delete;

	Ammunition(Configuration::Textures tex_id, const sf::Vector2f& boundaries, float deg_angle, float speed);
	
	virtual void update(const sf::Time& deltatime) = 0;

	float getRotation()const;
	float getRotationRad()const;
	void setRotation(float angle);
	void rotate(float angle);
	void setPosition(const sf::Vector2f& pos) override;
	
	float getSpriteRotation()const;
	void setSpriteRotation(float angle);
	void rotateSprite(float angle);

	bool getShouldBeDeleted();
};

class Laser :
	public Ammunition
{
private:

public:
	Laser(const Laser&) = delete;
	Laser& operator=(const Laser&) = delete;


	Laser(Configuration::Textures tex_id, const sf::Vector2f& boundaries, float deg_angle, float speed = 400.f);
	virtual ~Laser();

	void update(const sf::Time& deltatime);
};

class Missile :
	public Ammunition
{
private:
	Entity* m_Target;

public:
	Missile(Missile&) = delete;
	Missile& operator=(Missile&) = delete;


	Missile(Configuration::Textures tex_id, const sf::Vector2f& boundaries, float deg_angle, float speed = 400.f);

	void lockOnTarget(Entity* target);

	void update(const sf::Time& deltaTime);
};

class Beam :
	public Ammunition
{
private:

public:
	Beam(Beam&) = delete;
	Beam& operator=(Beam&) = delete;


	Beam(Configuration::Textures tex_id, const sf::Vector2f& boundaries, float deg_angle, float speed = 400.f);

	void update(const sf::Time& deltaTime);
};