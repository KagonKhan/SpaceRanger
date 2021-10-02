#pragma once
#include "EnemyShip.h"

class ScoutEnemyShip :
	public EnemyShip
{
private:
	void initWeapons();
	void updateIndividualBehavior(const sf::Time& deltaTime) override;
	void shoot(const sf::Time& deltaTime);

public:
	explicit ScoutEnemyShip();
	explicit ScoutEnemyShip(Configuration::TexturesShips tex_id);
	~ScoutEnemyShip() override;
};
