#pragma once
#include "Fleet.h"
class Level :
	public sf::Drawable
{
public:
	enum class EnemyShips {
		minigun, support, beam, rocket, scout, tank, scout_v2, stealth, boss,
	};

private:
	void draw(sf::RenderTarget& target, sf::RenderStates) const override;

#pragma region enemy init
	EnemyShip::ptr createEnemy(EnemyShips ship) const;
	EnemyShip::ptr createEnemyMinigun()			const;
	EnemyShip::ptr createEnemySupport()			const;
	EnemyShip::ptr createEnemyBeam()			const;
	EnemyShip::ptr createEnemyRocket()			const;
	EnemyShip::ptr createEnemyScout()			const;
	EnemyShip::ptr createEnemyTank()			const;
	EnemyShip::ptr createEnemyScoutV2()		    const;
	EnemyShip::ptr createEnemyStealth()		    const;
	EnemyShip::ptr createEnemyBoss()			const;
#pragma endregion

protected:
	sf::RenderWindow& m_Window;
	PlayerShip& m_Player;
	
	std::vector<Fleet> m_Enemies;
	std::vector<EnemyShip::ptr> m_EnemiesForDeletion;


	void updateEnemies(const sf::Time& deltaTime);

	void checkCollisions();
	void checkPlayerCollisions();
	void checkEnemyCollisions();
	void checkForDeletion();

public:
	Level(sf::RenderWindow& window, PlayerShip& player);

	void update(const sf::Time& deltaTime);



	void populateAreaWithEnemies(std::vector<EnemyShip::ptr>& container, EnemyShips enemyShip, sf::FloatRect area, sf::Vector2f padding);
	void addFleet(std::vector<EnemyShip::ptr> fleet);


	std::vector<Fleet>& getEnemies()	{			return m_Enemies;							}
	Fleet& getFleet(int index)			{			return m_Enemies.at(index);					}
	void addFleet(Fleet fleet)			{			m_Enemies.push_back(std::move(fleet));		}

};
