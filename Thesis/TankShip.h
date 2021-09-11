#pragma once
#include "EnemyShip.h"
class TankShip :
    public EnemyShip
{
private:

	void initWeapons();
	void updateIndividualBehavior(const sf::Time& deltaTime) override;
	void shoot(const sf::Time& deltaTime);

	void onDestroy() override;

public:
	TankShip(Configuration::TexturesShips tex_id);
	virtual ~TankShip();
};

