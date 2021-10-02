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
	void draw(sf::RenderTarget& target, sf::RenderStates) const override;
	int getMaxCap(const std::vector<Ammunition*> container) const;

protected:
	bool							m_AreActionsBlocked	   { false };	
	bool							m_CanBeDeleted		   { false };	// Everything done, can be deleted
	bool							m_MarkedForDeletion	   { false };	// Wants to be deleted
	std::vector<Ammunition*>		ammoOnScreen;


	virtual void updateWeapons(const sf::Time& deltaTime);
	virtual void updateCanBeDeleted();

	virtual void updateIndividualBehavior(const sf::Time& deltaTime) = 0;
	virtual void updateMovement(const sf::Time& deltaTime) = 0;


	virtual void repositionSprites();

public:
	Ship(float max_hp, Configuration::TexturesShips tex_id);

	void update(const sf::Time& deltaTime) override;


	void markForDeletion();
	void onDestroy() override;
	std::vector<Ammunition*>& getAmmoOnScreen();

	void setAreActionsBlocked(bool is_blocked);
	void setWeaponsAsActive(bool active) const;

	void move(const sf::Vector2f& moveBy);
	void setPosition(const sf::Vector2f& pos) override;

	void setPosition(float x, float y)		  override  {		setPosition(sf::Vector2f(x, y));	}
	bool canBeDeleted()						  const		{		return m_CanBeDeleted;				}	 
	bool shouldBeDeleted()					  const		{		return m_MarkedForDeletion;			}
	bool getAreActionsBlocked()				  const		{		return m_AreActionsBlocked;			}
};