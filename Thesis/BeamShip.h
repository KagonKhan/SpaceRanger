#pragma once
#include "EnemyShip.h"
class BeamShip :
    public EnemyShip
{
private:
	void initWeapons();
	void updateIndividualBehavior(const sf::Time& deltaTime) override;
	void shoot(const sf::Time& deltaTime);

public:
	explicit BeamShip();
	explicit BeamShip(Configuration::TexturesShips tex_id);

};

