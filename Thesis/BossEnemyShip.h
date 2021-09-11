#pragma once
#include "EnemyShip.h"
class BossEnemyShip :
	public EnemyShip
{
private:

	void initWeapons();
	void updateIndividualBehavior(const sf::Time& deltaTime) override;
	void shoot(const sf::Time& deltaTime);

	void onDestroy() override;

public:
	BossEnemyShip(Configuration::TexturesShips tex_id);
	virtual ~BossEnemyShip();
};
