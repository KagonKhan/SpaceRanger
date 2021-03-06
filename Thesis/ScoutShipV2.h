#pragma once
#include "EnemyShip.h"
class ScoutShipV2 :
    public EnemyShip
{
private:
	void initWeapons();
	void updateIndividualBehavior(const sf::Time& deltaTime) override;
	void shoot(const sf::Time& deltaTime);

public:
	explicit ScoutShipV2();
	explicit ScoutShipV2(Configuration::TexturesShips tex_id);

};

