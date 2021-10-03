#pragma once
#include "Entity.h"
#include "IsLiving.h"
#include "HasWeapons.h"
#include "CanCollide.h"

class Ship :
	public Entity, 
	public IsLiving,
	public HasWeapons,
	public CanCollide
{
private:
	int getMaxCap(const std::vector<Ammunition*> container) const;

protected:
	bool							m_AreActionsBlocked	   { false };	
	std::vector<Ammunition*>		ammoOnScreen; 
	OnDestroy m_OnDestroy;




	virtual void updateWeapons(const sf::Time& deltaTime);
	virtual void updateOnDestroy(const sf::Time& deltaTime);
	virtual void updateIndividualBehavior(const sf::Time& deltaTime) = 0;
	virtual void updateMovement(const sf::Time& deltaTime) = 0;

	virtual void repositionSprites(sf::Vector2f positionAt);

public:
	Ship(float max_hp, Configuration::TexturesShips tex_id);

	void update(const sf::Time& deltaTime) override;


	std::vector<Ammunition*>& getAmmoOnScreen();

	void setAreActionsBlocked(bool is_blocked);
	void setWeaponsAsActive(bool active) const;


	void move(const sf::Vector2f& moveBy)				{		repositionSprites(m_Position + moveBy); }
	void setPosition(const sf::Vector2f& pos) override	{		repositionSprites(pos);					}
	void setPosition(float x, float y)		  override  {		setPosition(sf::Vector2f(x, y));		}
	bool getAreActionsBlocked()				  const		{		return m_AreActionsBlocked;				}
};