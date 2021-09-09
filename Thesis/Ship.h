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

	void update(const sf::Time& deltaTime)override final;

	void setPosition(const sf::Vector2f& pos) override;
	void setPosition(float x, float y) override;

	void setAreActionsBlocked(bool is_blocked);
	bool getAreActionsBlocked() const;


	std::vector<Ammunition*>& getShots();

	bool canBeDeleted();
	bool shouldBeDeleted();
	void markForDeletion();
};