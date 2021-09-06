#pragma once
#include "Entity.h"
#include "CanCollide.h"

#include "AnimatedSprite.h"

# define M_PIl          3.141592653589793238462643383279502884L /* pi */


class Weapon;
class Ammunition :
	public Entity,
	public CanCollide
{
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void setRadAngle();
	virtual void initAnimation() = 0;
	virtual void updateIndividualBehavior(const sf::Time& deltaTime) = 0;
	void updateAnimation(const sf::Time& deltaTime);
	void updatePosition(const sf::Time& deltaTime);

protected:
	float m_Speed;
	float m_DegAngle;
	float m_RadAngle;
	bool m_ShouldBeDeleted;

	Weapon* m_ParentWeapon;

	sf::Vector2f m_Boundaries;

	Animation m_Animation;
	AnimatedSprite m_AnimatedSprite;


public:
	Ammunition(Ammunition&) = delete;
	Ammunition& operator=(Ammunition&) = delete;

	Ammunition(Configuration::TexturesWeaponry tex_id, const sf::Vector2f& boundaries, float deg_angle, float speed, Weapon* parent = nullptr);
	
	void update(const sf::Time& deltaTime) override;

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
	void initAnimation() override;
	void updateIndividualBehavior(const sf::Time& deltaTime) override;

public:
	Laser(const Laser&) = delete;
	Laser& operator=(const Laser&) = delete;


	Laser(Configuration::TexturesWeaponry tex_id, const sf::Vector2f& boundaries, float deg_angle, float speed = 400.f, Weapon* parent = nullptr);
	virtual ~Laser();

};

class Missile :
	public Ammunition
{
private:
	void initAnimation() override;
	void updateIndividualBehavior(const sf::Time& deltaTime) override final;
	void updateTrackingSystem(const sf::Time& deltaTime);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override final;
	
	/* For Target-seeking missiles */
	/* MEME possibility std::optional<std::reference_wrapper<Entity>> */
	const Entity* m_Target;
	float m_RotationRadius;
	float m_SeekingDistance;
	float m_FuelDuration;

public:
	Missile(Missile&) = delete;
	Missile& operator=(Missile&) = delete;


	Missile(Configuration::TexturesWeaponry tex_id, Configuration::TexturesWeaponry thrusters, const sf::Vector2f& boundaries, float deg_angle, float speed = 400.f, Weapon* parent = nullptr);

	void lockOnTarget(const Entity* target);

};


/* There's issue with this design. Others weapons are just launch the bullets are done.
This particular weapon shoots constantly. Might want to figure out a different approach */
class Beam :
	public Ammunition
{
private:
	void initAnimation() override;
	void updateIndividualBehavior(const sf::Time& deltaTime) override;

public:
	Beam(Beam&) = delete;
	Beam& operator=(Beam&) = delete;


	Beam(Configuration::TexturesWeaponry tex_id, const sf::Vector2f& boundaries, float deg_angle, float speed = 400.f, Weapon* parent = nullptr);

};