#pragma once
#include "Ship.h"
#include "EnemyShip.h"

class ScoutEnemyShip :
	public EnemyShip

{
private:
	
	void initWeapons();

public:
	ScoutEnemyShip(Configuration::TexturesShips tex_id);
	virtual ~ScoutEnemyShip();


	void update(const sf::Time& deltaTime);

};
