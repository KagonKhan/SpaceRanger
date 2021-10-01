#pragma once
#include "EnemyShip.h"
class StealthShip :
    public EnemyShip
{
private:
	void initWeapons();
	void updateIndividualBehavior(const sf::Time& deltaTime) override;
	void shoot(const sf::Time& deltaTime);

	void onDestroy() override;

public:
	explicit StealthShip();
	explicit StealthShip(Configuration::TexturesShips tex_id);
	~StealthShip() override;
};

