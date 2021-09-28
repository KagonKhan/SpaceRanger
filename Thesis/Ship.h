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

protected:

	std::vector<Ammunition*> ghostPTR;

	bool m_AreActionsBlocked;
	bool m_CanBeDeleted;
	bool m_MarkedForDeletion;


	virtual void updateMovement(const sf::Time& deltaTime);
	virtual void updatePosition(const sf::Time& deltaTime);
	virtual void updateSprites(const sf::Time& deltaTime);
	virtual void updateWeapons(const sf::Time& deltaTime);
	virtual void updateIndividualBehavior(const sf::Time& deltaTime) = 0;

	virtual void onDestroy();

public:
	Ship(double max_hp, Configuration::TexturesShips tex_id);
	virtual ~Ship();

	void update(const sf::Time& deltaTime)override;

	void setPosition(const sf::Vector2f& pos) override;

	void setAreActionsBlocked(bool is_blocked);
	void setWeaponsAsActive(bool enabled);


	void markForDeletion();

	std::vector<Ammunition*>& getShots();

	bool canBeDeleted() const {		return m_CanBeDeleted;	} 
	bool shouldBeDeleted()const { return m_MarkedForDeletion; }
	bool getAreActionsBlocked() const { return m_AreActionsBlocked; }
	void setPosition(float x, float y) override { setPosition(sf::Vector2f(x, y)); }
};