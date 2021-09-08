#pragma once
#include "Entity.h"

class Level :
	public sf::Drawable
{
private:
	void draw(sf::RenderTarget& target, sf::RenderStates) const;
	sf::RenderWindow& m_Window;
	std::vector<Entity::ptr> m_Entities;
	enum class EnemyShips{
		minigun, support, beam, rocket, scout, tank, scout_v2, stealth, boss,
	};

	void populateAreaWithEnemies(std::vector<Entity::ptr>& container, EnemyShips enemyShip, sf::FloatRect area, sf::Vector2f padding);
	Entity::ptr createEnemy(EnemyShips ship);
		Entity::ptr createEnemyMinigun();
		Entity::ptr createEnemySupport();
		Entity::ptr createEnemyBeam();
		Entity::ptr createEnemyRocket();
		Entity::ptr createEnemyScout();
		Entity::ptr createEnemyTank();
		Entity::ptr createEnemyScoutV2();
		Entity::ptr createEnemyStealth();
		Entity::ptr createEnemyBoss();

public:
	Level(sf::RenderWindow& window);
	~Level();
	
	void update(const sf::Time& deltaTime);
};
