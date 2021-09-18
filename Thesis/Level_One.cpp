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
		std::vector<EnemyShip::ptr> enemies;
		m_Level.populateAreaWithEnemies(enemies, Level::EnemyShips::scout, sf::FloatRect(0, -700, Configuration::boundaries.x, 400), sf::Vector2f(5, 5));
		
		for (auto&& enemy : enemies)
			enemy->setAreActionsBlocked(true);

		m_Level.addFleet(std::move(enemies));
		firstTime = false;
		return;
	}
	static auto&& fleet = m_Level.getFleet(0);

	if(fleet.getRectangle().top > 0)
		for (auto&& enemy : fleet)
			enemy->setAreActionsBlocked(false);
	else
		fleet.move(sf::Vector2f(0, 100) * deltaTime.asSeconds());


	if (fleet.size() == 0)
		m_CurrentPhase = Phases::two;
}
void Level_One::phaseTwo(const sf::Time& deltaTime)
{
	static bool firstTime = true;

	if (firstTime) {
		std::vector<EnemyShip::ptr> enemies;
		m_Level.populateAreaWithEnemies(enemies, Level::EnemyShips::tank, sf::FloatRect(0, -700, Configuration::boundaries.x, 400), sf::Vector2f(5, 5));

		for (auto&& enemy : enemies)
			enemy->setAreActionsBlocked(true);

		m_Level.addFleet(std::move(enemies));
		firstTime = false;
		return;
	}
	static auto&& fleet = m_Level.getFleet(0);
	static float time = 0;
	time += deltaTime.asSeconds();
	if (fleet.getRectangle().top > 0) {
		sf::Vector2f moveBy;
		moveBy.x = sinf(time);
		moveBy.y = cosf(time);

		fleet.move(moveBy);

	}
	else
		fleet.move(sf::Vector2f(0, 100) * deltaTime.asSeconds());
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
