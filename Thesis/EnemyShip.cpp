#include "pch.h"
#include "EnemyShip.h"

EnemyShip::EnemyShip(float maxHp, Configuration::TexturesShips tex_id)
	: Ship(maxHp, tex_id)
{
}

EnemyShip::~EnemyShip()
{
}
