#pragma once
#include "Ship.h"
class EnemyShip :
	public Ship
{
private:


public:
	EnemyShip(float maxHp,Configuration::TexturesShips tex_id);
	virtual ~EnemyShip();
};