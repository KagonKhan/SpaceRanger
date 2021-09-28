#include "pch.h"
#include "LevelManagerOne.h"

LevelManagerOne::LevelManagerOne(Level& level)
	: LevelManager(level)
{
	m_CurrentPhase = Phases::three;
}


void LevelManagerOne::update(const sf::Time& deltaTime)
{
	updatePhase(deltaTime);

	m_Level.update(deltaTime);
}


void LevelManagerOne::initFleet(Level::EnemyShips type, sf::FloatRect area, sf::Vector2f padding)
{
	std::vector<EnemyShip::ptr> enemies;
	m_Level.populateAreaWithEnemies(enemies, type, area, padding);

	for (auto&& enemy : enemies) 
		enemy->setWeaponsAsActive(false);
	

	m_Level.addFleet(std::move(enemies));
}

void LevelManagerOne::updatePhase(const sf::Time& deltaTime)
{
	switch (m_CurrentPhase)
	{
	case Phases::one:		phaseOne(deltaTime);		break;
	case Phases::two:		phaseTwo(deltaTime);		break;
	case Phases::three:		phaseThree(deltaTime);		break;
	case Phases::four:		phaseFour(deltaTime);		break;
	case Phases::five:		phaseFive(deltaTime);		break;
	case Phases::six:		phaseSix(deltaTime);		break;
	case Phases::seven:		phaseSeven(deltaTime);		break;
	case Phases::eight:		phaseEight(deltaTime);		break;
	case Phases::nine:		phaseNine(deltaTime);		break;
	default:											break;
	}
}


void LevelManagerOne::phaseOne(const sf::Time& deltaTime)
{

	if (static bool firstTime = true; firstTime) {
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


void LevelManagerOne::phaseTwo(const sf::Time& deltaTime)
{


	if (static bool firstTime = true; firstTime) {
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
			ship->setWeaponsAsActive(true);
	}
	else
		fleet1.move(sf::Vector2f( 200, 0) * deltaTime.asSeconds());


	if (fleet2.getRectangle().left + fleet2.getRectangle().width < Configuration::boundaries.x) {
		for (auto&& ship : fleet2)
			ship->setWeaponsAsActive(true);
	}
	else
		fleet2.move(sf::Vector2f(-200, 0) * deltaTime.asSeconds());


	if (fleet1.size() == 0 && fleet2.size() == 0)
		m_CurrentPhase = Phases::three;
}



void LevelManagerOne::phaseThree(const sf::Time& deltaTime)
{



	if (static bool firstTime = true; firstTime) {
		initFleet(Level::EnemyShips::stealth, sf::FloatRect(-200, -1000, 450, 800), sf::Vector2f(5, 5));
		initFleet(Level::EnemyShips::stealth, sf::FloatRect(Configuration::boundaries.x, -1000, 450, 800), sf::Vector2f(5, 5));


		std::vector<sf::Vector2f> path = { {75, 86},{1850, 906},{80, 866},{930, -144},{1850, 906},{80, 866},{1855, 91} };

		m_Level.getFleet(0).setPath(path);
		firstTime = false;
		return;
	}

	static auto&& fleet1 = m_Level.getFleet(0);
	static auto&& fleet2 = m_Level.getFleet(1);

	static float time = 0;
	time += deltaTime.asSeconds();


	if (fleet1.getRectangle().left < 0)
		;
	else if (fleet1.getRectangle().top < 0) {
		;
	}
	else
		for (auto&& ship : fleet1)
			ship->setWeaponsAsActive(true);




	if (fleet2.getRectangle().left + fleet2.getRectangle().width > Configuration::boundaries.x) 
		fleet2.move(sf::Vector2f(-200, 0) * deltaTime.asSeconds());
	else if (fleet2.getRectangle().top < 0) {
		fleet2.move(sf::Vector2f(0, 200) * deltaTime.asSeconds());
	}
	else
		for (auto&& ship : fleet2)
			ship->setWeaponsAsActive(true);



	if (fleet1.size() == 0 && fleet2.size() == 0)
		m_CurrentPhase = Phases::four;
}







void LevelManagerOne::phaseFour(const sf::Time& deltaTime)
{
}
void LevelManagerOne::phaseFive(const sf::Time& deltaTime)
{
}
void LevelManagerOne::phaseSix(const sf::Time& deltaTime)
{
}
void LevelManagerOne::phaseSeven(const sf::Time& deltaTime)
{
}
void LevelManagerOne::phaseEight(const sf::Time& deltaTime)
{
}
void LevelManagerOne::phaseNine(const sf::Time& deltaTime)
{
}
