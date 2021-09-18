#include "pch.h"
#include "Level_One.h"

Level_One::Level_One(Level& level)
	: LevelManager(level)
{
	init();
}

Level_One::~Level_One()
{
}

void Level_One::init()
{
	std::vector<EnemyShip::ptr> enemies;
	m_Level.populateAreaWithEnemies(enemies, Level::EnemyShips::beam, sf::FloatRect(200, 200, 1000, 200), sf::Vector2f(5, 5));
	m_Level.addGroupOfEnemies(std::move(enemies));

}
void Level_One::phaseOne(const sf::Time& deltaTime)
{
}
void Level_One::phaseTwo(const sf::Time& deltaTime)
{
}
void Level_One::phaseThree(const sf::Time& deltaTime)
{
}
void Level_One::phaseFour(const sf::Time& deltaTime)
{
}
void Level_One::phaseFive(const sf::Time& deltaTime)
{
}
void Level_One::phaseSix(const sf::Time& deltaTime)
{
}
void Level_One::phaseSeven(const sf::Time& deltaTime)
{
}
void Level_One::phaseEight(const sf::Time& deltaTime)
{
}
void Level_One::phaseNine(const sf::Time& deltaTime)
{
}
void Level_One::update(const sf::Time& deltaTime)
{
	m_Level.update(deltaTime);
}
