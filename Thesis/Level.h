#pragma once
#include "Fleet.h"
class Level :
	public sf::Drawable
{
private:
	void draw(sf::RenderTarget& target, sf::RenderStates) const;

protected:
	sf::RenderWindow& m_Window;
	PlayerShip& m_Player;
	
	std::vector<Fleet> m_Enemies;


	void updateEnemies(const sf::Time& deltaTime);

	void checkCollisions();
	void checkPlayerCollisions();
	void checkEnemyCollisions();
	void checkForDeletion();

public:
	Level(sf::RenderWindow& window, PlayerShip& player);
	virtual ~Level();
	
	void update(const sf::Time& deltaTime);

	enum class EnemyShips {
		minigun, support, beam, rocket, scout, tank, scout_v2, stealth, boss,
	};

	void populateAreaWithEnemies(std::vector<EnemyShip::ptr>& container, EnemyShips enemyShip, sf::FloatRect area, sf::Vector2f padding);
	std::vector<Fleet>& getEnemies();
	void addFleet(std::vector<EnemyShip::ptr> fleet);
	Fleet& getFleet(int index);

#pragma region enemy init
private :
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
};
