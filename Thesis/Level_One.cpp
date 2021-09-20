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
	m_CurrentPhase = Phases::one;
}

void Level_One::update(const sf::Time& deltaTime)
{
	updatePhase(deltaTime);

	m_Level.update(deltaTime);
}


void Level_One::initFleet(Level::EnemyShips type, sf::FloatRect area, sf::Vector2f padding)
{
	std::vector<EnemyShip::ptr> enemies;
	m_Level.populateAreaWithEnemies(enemies, type, area, padding);

	for (auto&& enemy : enemies) 
		enemy->setAreActionsBlocked(true);
	

	m_Level.addFleet(std::move(enemies));
}

void Level_One::updatePhase(const sf::Time& deltaTime)
{
	switch (m_CurrentPhase)
	{
	case Level_One::Phases::one:		phaseOne(deltaTime);
		break;
	case Level_One::Phases::two:		phaseTwo(deltaTime);
		break;
	case Level_One::Phases::three:		phaseThree(deltaTime);
		break;
	case Level_One::Phases::four:		phaseFour(deltaTime);
		break;
	case Level_One::Phases::five:		phaseFive(deltaTime);
		break;
	case Level_One::Phases::six:		phaseSix(deltaTime);
		break;
	case Level_One::Phases::seven:		phaseSeven(deltaTime);
		break;
	case Level_One::Phases::eight:		phaseEight(deltaTime);
		break;
	case Level_One::Phases::nine:		phaseNine(deltaTime);
		break;
	default:
		break;
	}
}


void Level_One::phaseOne(const sf::Time& deltaTime)
{
	static bool firstTime = true;

	if (firstTime) {
		initFleet(Level::EnemyShips::scout, sf::FloatRect(0, -700, Configuration::boundaries.x, 400), sf::Vector2f(5, 5));
		firstTime = false;
		return;
	}

	static auto&& fleet = m_Level.getFleet(0);













	if (fleet.getRectangle().top > 0)
		for (auto&& ship : fleet) 
			ship->setAreActionsBlocked(false);	
	else
		fleet.move(sf::Vector2f(0, 100) * deltaTime.asSeconds());


	if (fleet.size() == 0)
		m_CurrentPhase = Phases::two;
}


void Level_One::phaseTwo(const sf::Time& deltaTime)
{
	static bool firstTime = true;
	
	if (firstTime) {
		initFleet(Level::EnemyShips::scout, sf::FloatRect(-985, 0, Configuration::boundaries.x / 2.f - 100, 400), sf::Vector2f(5, 5));
		initFleet(Level::EnemyShips::scout, sf::FloatRect(2000, 0, Configuration::boundaries.x / 2.f  - 100, 400), sf::Vector2f(5, 5));

		firstTime = false;
		return;
	}
	static auto&& fleet1 = m_Level.getFleet(0);
	static auto&& fleet2 = m_Level.getFleet(1);

	static float time = 0;
	time += deltaTime.asSeconds();


	if (fleet1.getRectangle().left > 0) {
		for (auto&& ship : fleet1)
			ship->setAreActionsBlocked(false);
	}
	else
		fleet1.move(sf::Vector2f( 200, 0) * deltaTime.asSeconds());


	if (fleet2.getRectangle().left + fleet2.getRectangle().width < Configuration::boundaries.x) {
		for (auto&& ship : fleet2)
			ship->setAreActionsBlocked(false);
	}
	else
		fleet2.move(sf::Vector2f(-200, 0) * deltaTime.asSeconds());
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
