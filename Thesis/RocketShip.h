#pragma once
#include "EnemyShip.h"
class RocketShip :
    public EnemyShip
{
private:
	void initWeapons();
	void updateIndividualBehavior(const sf::Time& deltaTime) override;
	void shoot(const sf::Time& deltaTime);

	void onDestroy() override;

public:
	RocketShip(Configuration::TexturesShips tex_id);
	virtual ~RocketShip();
};

