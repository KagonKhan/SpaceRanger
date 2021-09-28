#pragma once
#include "EnemyShip.h"
class MinigunShip :
    public EnemyShip
{
private:

	void initWeapons();
	void updateIndividualBehavior(const sf::Time& deltaTime) override;
	void shoot(const sf::Time& deltaTime);

	void onDestroy() override;

public:
	explicit MinigunShip(Configuration::TexturesShips tex_id);
};

