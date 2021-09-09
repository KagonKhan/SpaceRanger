#pragma once
#include "Ship.h"
#include "EnemyShip.h"

class ScoutEnemyShip :
	public EnemyShip

{
private:
	
	void initWeapons();
	void updateIndividualBehavior(const sf::Time& deltaTime) override;
	void shoot(const sf::Time& deltaTime);

public:
	ScoutEnemyShip(Configuration::TexturesShips tex_id);
	virtual ~ScoutEnemyShip();
};
