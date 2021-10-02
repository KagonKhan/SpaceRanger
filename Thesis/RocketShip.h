#pragma once
#include "EnemyShip.h"
class RocketShip :
    public EnemyShip
{
private:
	void initWeapons();
	void updateIndividualBehavior(const sf::Time& deltaTime) override;
	void shoot(const sf::Time& deltaTime);

public:
	explicit RocketShip();
	explicit RocketShip(Configuration::TexturesShips tex_id);

};

