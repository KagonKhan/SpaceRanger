#pragma once
#include "EnemyShip.h"
class BossEnemyShip :
	public EnemyShip
{
private:

	void initWeapons();
	void updateIndividualBehavior(const sf::Time& deltaTime) override;
	void shoot(const sf::Time& deltaTime);


public:
	explicit BossEnemyShip();
	explicit BossEnemyShip(Configuration::TexturesShips tex_id);
	~BossEnemyShip() override;
};
