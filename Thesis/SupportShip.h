#pragma once
#include "EnemyShip.h"
class SupportShip :
    public EnemyShip
{
private:

	void initWeapons();
	void updateIndividualBehavior(const sf::Time& deltaTime) override;
	void shoot(const sf::Time& deltaTime);

	void onDestroy() override;

public:
	SupportShip(Configuration::TexturesShips tex_id);
	virtual ~SupportShip();
};

