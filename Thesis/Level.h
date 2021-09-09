#pragma once
#include "EnemyShip.h"

class Level :
	public sf::Drawable
{
private:
	void draw(sf::RenderTarget& target, sf::RenderStates) const;
	sf::RenderWindow& m_Window;
	PlayerShip& m_Player;
	
	
	std::vector<EnemyShip::ptr> m_Enemies;
	std::vector<EnemyShip::ptr> m_EnemiesForDeletion;

	enum class EnemyShips{
		minigun, support, beam, rocket, scout, tank, scout_v2, stealth, boss,
	};

#pragma region INIT/ENEMY

	void populateAreaWithEnemies(std::vector<EnemyShip::ptr>& container, EnemyShips enemyShip, sf::FloatRect area, sf::Vector2f padding);
	EnemyShip::ptr createEnemy(EnemyShips ship);
		EnemyShip::ptr createEnemyMinigun();
		EnemyShip::ptr createEnemySupport();
		EnemyShip::ptr createEnemyBeam();
		EnemyShip::ptr createEnemyRocket();
		EnemyShip::ptr createEnemyScout();
		EnemyShip::ptr createEnemyTank();
		EnemyShip::ptr createEnemyScoutV2();
		EnemyShip::ptr createEnemyStealth();
		EnemyShip::ptr createEnemyBoss();
#pragma endregion

	void checkCollisions();
	void checkPlayerCollisions();
	void checkEnemyCollisions();
	void checkForDeletion();

public:
	Level(sf::RenderWindow& window, PlayerShip& player);
	virtual ~Level();
	
	void update(const sf::Time& deltaTime);
};
