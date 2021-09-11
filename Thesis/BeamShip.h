#pragma once
#include "EnemyShip.h"
class BeamShip :
    public EnemyShip
{
private:

	void initWeapons();
	void updateIndividualBehavior(const sf::Time& deltaTime) override;
	void shoot(const sf::Time& deltaTime);

	void onDestroy() override;

public:
	BeamShip(Configuration::TexturesShips tex_id);
	virtual ~BeamShip();
};

