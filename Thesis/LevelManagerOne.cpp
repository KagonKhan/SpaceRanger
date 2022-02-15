#include "pch.h"
#include "LevelManagerOne.h"
#include "Game.h"

using namespace pos;
LevelManagerOne::LevelManagerOne(Level& level)
	: LevelManager(level)
{
	m_CurrentPhase = Phases::one;




	Fleet::PositionType setPosition = std::make_tuple(X::Middle, Place::Inside, Y::Top, Place::Outside);
	auto&& fleet = addFleet(EnemyShip::Type::scout, sf::FloatRect(0, 0, Configuration::boundaries.x, 400), sf::Vector2f(50, 50), setPosition);
	float length = fleet.getRectangle().top;
	fleet.addMovementToQueue({ 0.f, 1.f }, length);
}


void LevelManagerOne::update(const sf::Time& deltaTime)
{
	updatePhase(deltaTime);

	m_Level.update(deltaTime);
}




Fleet& LevelManagerOne::addFleet(EnemyShip::Type type, sf::FloatRect area, sf::Vector2f padding, std::optional<Fleet::PositionType> pos)
{
	Fleet fleet(type, area, padding, false);
	fleet.setWeaponsAsActive(false);

	if (pos.has_value())
		fleet.setPosition(pos.value());

	return m_Level.addFleet(std::move(fleet));
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
	case Phases::six:		phaseSix(deltaTime);			break;
	//case Phases::seven:		phaseSeven(deltaTime);		break;
	//case Phases::eight:		phaseEight(deltaTime);		break;
	//case Phases::nine:		phaseNine(deltaTime);		break;
	default:											break;
	}
}


void LevelManagerOne::phaseOne(const sf::Time&)
{
	if (m_Level.getEnemies().empty()) {
		m_CurrentPhase = Phases::two;


		Fleet::PositionType position1 = std::make_tuple(X::Left, Place::Outside, Y::Top, Place::Inside);
		auto&& fleet1 = addFleet(EnemyShip::Type::scout, sf::FloatRect(0, 0, Configuration::boundaries.x / 2.f - 100, 400), sf::Vector2f(35, 35), position1);
		float length = fleet1.getRectangle().width;

		Fleet::PositionType position2 = std::make_tuple(X::Right, Place::Outside, Y::Top, Place::Inside);
		auto&& fleet2 = addFleet(EnemyShip::Type::scout, sf::FloatRect(0, 0, Configuration::boundaries.x / 2.f - 100, 400), sf::Vector2f(35, 35), position2);
		
		m_Level.getFleetPtr(0)->addMovementToQueue({  1.f, 0.f }, length);
		m_Level.getFleetPtr(1)->addMovementToQueue({ -1.f, 0.f }, length);

	}
}

void LevelManagerOne::phaseTwo(const sf::Time&)
{
	if (m_Level.getEnemies().empty()) {
		m_CurrentPhase = Phases::three;


		Fleet::PositionType position1 = std::make_tuple(X::Left, Place::Inside, Y::Top, Place::Outside);
		addFleet(EnemyShip::Type::stealth, sf::FloatRect(0, 0, 200, 400), sf::Vector2f(5, 5), position1);

		Fleet::PositionType position2 = std::make_tuple(X::Right, Place::Inside, Y::Top, Place::Outside);
		addFleet(EnemyShip::Type::stealth, sf::FloatRect(0, 0, 200, 400), sf::Vector2f(5, 5), position2);



		std::vector<sf::Vector2f> wp = { {75, 86},{1850, 906},{80, 866},{930, -144},{1850, 906},{80, 866},{1855, 91} };
		Spline path(wp, 0.01f, true);


		m_Level.getFleetPtr(0)->setPath(path);
		m_Level.getFleetPtr(1)->setPath(path.getMirroredPath(true));
	}

}



void LevelManagerOne::phaseThree(const sf::Time& deltaTime)
{

	if (m_Level.getEnemies().empty()) {
		m_CurrentPhase = Phases::four;

		Fleet::PositionType position1 = std::make_tuple(X::Left, Place::Outside, Y::Top, Place::Inside);
		auto&& fleet1 = addFleet(EnemyShip::Type::rocket, sf::FloatRect(0, 0, Configuration::boundaries.x / 2.f - 100, 400), sf::Vector2f(100, 35), position1);
		float length = fleet1.getRectangle().width;

		Fleet::PositionType position2 = std::make_tuple(X::Right, Place::Outside, Y::Top, Place::Inside);
		auto&& fleet2 = addFleet(EnemyShip::Type::rocket, sf::FloatRect(0, 0, Configuration::boundaries.x / 2.f - 100, 400), sf::Vector2f(100, 35), position2);

		m_Level.getFleetPtr(0)->addMovementToQueue({ 1.f, 0.f }, length);
		m_Level.getFleetPtr(1)->addMovementToQueue({ -1.f, 0.f }, length);
	}
}







void LevelManagerOne::phaseFour(const sf::Time&)
{
	if (m_Level.getEnemies().empty()) {
		m_CurrentPhase = Phases::five;


		Fleet::PositionType position1 = std::make_tuple(X::Left, Place::Outside, Y::Top, Place::Inside);
		auto&& fleet1 = addFleet(EnemyShip::Type::minigun, sf::FloatRect(0, 0, Configuration::boundaries.x / 2.f - 100, 400), sf::Vector2f(55, 55), position1);
		float length = fleet1.getRectangle().width;

		Fleet::PositionType position2 = std::make_tuple(X::Right, Place::Outside, Y::Top, Place::Inside);
		auto&& fleet2 = addFleet(EnemyShip::Type::minigun, sf::FloatRect(0, 0, Configuration::boundaries.x / 2.f - 100, 400), sf::Vector2f(55, 55), position2);

		m_Level.getFleetPtr(0)->addMovementToQueue({ 1.f, 0.f }, length);
		m_Level.getFleetPtr(1)->addMovementToQueue({ -1.f, 0.f }, length);


		Game::getInstance()->setGameSpeed(0.25f);
	}
}



void LevelManagerOne::phaseFive(const sf::Time&)
{
	if (m_Level.getEnemies().empty()) {
		m_CurrentPhase = Phases::six;
	}
}



void LevelManagerOne::phaseSix(const sf::Time&)
{
	Game::getInstance()->setGameSpeed(2.f);
	m_IsFinished = true;
}
