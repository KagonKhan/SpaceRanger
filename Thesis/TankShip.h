#pragma once
#include "EnemyShip.h"
class TankShip :
    public EnemyShip
{
private:

	void initWeapons();
	void updateIndividualBehavior(const sf::Time& deltaTime) override;
	void shoot(const sf::Time& deltaTime);

public:
	explicit TankShip();
	explicit TankShip(Configuration::TexturesShips tex_id);

};

