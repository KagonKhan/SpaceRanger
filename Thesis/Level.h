#pragma once
#include "Fleet.h"
class Level :
	public sf::Drawable
{

private:
	void draw(sf::RenderTarget& target, sf::RenderStates) const override;

protected:
	sf::RenderWindow& m_Window;
	PlayerShip& m_Player;
	

	// Possibly incorrect choice - vector resize invalidates pointers
	std::vector<Fleet> m_Enemies;
	std::vector<sf::RectangleShape> m_rects;
	std::vector<EnemyShip::ptr> m_EnemiesForDeletion;


	void updateEnemies(const sf::Time& deltaTime);

	void checkCollisions();
	void checkPlayerCollisions();
	void checkEnemyCollisions();
	void checkForDeletion();


	void addRect();

public:
	const sf::RenderWindow& getWindow()const { return m_Window; }
	Level(sf::RenderWindow& window, PlayerShip& player);

	void update(const sf::Time& deltaTime);


	void clearRects() { m_rects.clear(); }
	void addFleet(std::vector<EnemyShip::ptr> fleet);
	void addFleet(Fleet fleet);


	std::vector<Fleet>& getEnemies()	{			return m_Enemies;							}
	Fleet& getFleet(int index)			{			return m_Enemies.at(index);					}
	Fleet* getFleetPtr(int index)		{			return &m_Enemies.at(index);				}

};
