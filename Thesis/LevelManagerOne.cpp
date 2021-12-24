#include "pch.h"
#include "LevelManagerOne.h"
using namespace pos;
LevelManagerOne::LevelManagerOne(Level& level)
	: LevelManager(level)
{
	m_CurrentPhase = Phases::one;

	/*
	PhaseFunction phase_one;
	phase_one.function = [this](const sf::Time& deltaTime) {
		static Fleet* fleet = nullptr;
		if (static bool firstTime = true; firstTime) {

			Fleet::PositionType setPosition = std::make_tuple(X::Middle, Place::Inside, Y::Top, Place::Outside);


			initFleet(EnemyShip::Type::scout, sf::FloatRect(0, 0, Configuration::boundaries.x, 400),
				sf::Vector2f(5, 5),	setPosition);

			fleet = m_Level.getFleetPtr(0);

			auto rect = fleet->getRectangle();
			float length = -rect.top;


			fleet->addMovementToQueue({0.f, 1.f}, length);
			fleet->addMovementToQueue({0.f, 1.f}, length/2.f);
			fleet->addMovementToQueue({0.f, -1.f}, length/2.f);
			
			fleet->addMovementToQueue({1.f,	 0.f}, length/2.f);
			fleet->addMovementToQueue({-1.f,  0.f}, length/2.f);

			fleet->addMovementToQueue({-10.f, -10.f}, length/2.f);
			fleet->addMovementToQueue({10.f, 10.f}, length/2.f);
			
			
			firstTime = false;
			return;
		}

		if (fleet->getRectangle().top > 0)
			for (auto&& ship : *fleet)
				ship->setWeaponsAsActive(true);



		if (fleet->size() == 0) {
			m_Level.clearRects();
			phases.pop();
		}
	};

	phases.push(phase_one);


	PhaseFunction phase_two;
	phase_two.function = [this](const sf::Time& deltaTime) {
		static Fleet* fleet[2]{ nullptr,nullptr };

		if (static bool firstTime = true; firstTime) {
			Fleet::PositionType position1 = std::make_tuple(X::Left, Place::Outside, Y::Top, Place::Inside);


			initFleet(EnemyShip::Type::scout,
				sf::FloatRect(0, 0, Configuration::boundaries.x / 2.f - 100, 400),
				sf::Vector2f(5, 5),
				position1

			);

			Fleet::PositionType position2 = std::make_tuple(X::Right, Place::Outside, Y::Top, Place::Inside);

			initFleet(EnemyShip::Type::scout,
				sf::FloatRect(0, 0, Configuration::boundaries.x / 2.f - 100, 400),
				sf::Vector2f(5, 5),
				position2

			);

			firstTime = false;

			fleet[0] = m_Level.getFleetPtr(0);

			fleet[1] = m_Level.getFleetPtr(1);
			return;
		}









		static float time = 0;
		time += deltaTime.asSeconds();


		if (fleet[0]->getRectangle().left > 0) {
			for (auto&& ship : *fleet[0])
				ship->setWeaponsAsActive(true);
		}
		else
			fleet[0]->move(sf::Vector2f(200, 0) * deltaTime.asSeconds());


		if (fleet[1]->getRectangle().left + fleet[1]->getRectangle().width < Configuration::boundaries.x) {
			for (auto&& ship : *fleet[1])
				ship->setWeaponsAsActive(true);
		}
		else
			fleet[1]->move(sf::Vector2f(-200, 0) * deltaTime.asSeconds());


		if (fleet[0]->size() == 0 && fleet[1]->size() == 0) {
			m_CurrentPhase = Phases::three;
			m_Level.clearRects();
		}
	};

	phases.push(phase_two);



	PhaseFunction phase_three;
	phase_three.function = [this](const sf::Time& deltaTime) {
		static Fleet* fleet[2]{ nullptr,nullptr };

		if (static bool firstTime = true; firstTime) {
			Fleet::PositionType position1 = std::make_tuple(X::Left, Place::Inside, Y::Top, Place::Outside);

			initFleet(EnemyShip::Type::stealth,
				sf::FloatRect(0, 0, 450, 800),
				sf::Vector2f(5, 5),
				position1
			);


			Fleet::PositionType position2 = std::make_tuple(X::Right, Place::Inside, Y::Top, Place::Outside);
			initFleet(EnemyShip::Type::stealth,
				sf::FloatRect(0, 0, 450, 800),
				sf::Vector2f(5, 5),
				position2
			);


			std::vector<sf::Vector2f> wp = { {75, 86},{1850, 906},{80, 866},{930, -144},{1850, 906},{80, 866},{1855, 91} };
			Spline path(wp, 0.01f, true);

			fleet[0] = m_Level.getFleetPtr(0);
			fleet[0]->setPath(path);
			fleet[1] = m_Level.getFleetPtr(1);
			fleet[1]->setPath(path.getMirroredPath(true));
			firstTime = false;
			return;
		}




		static float time = 0;
		time += deltaTime.asSeconds();


		if (fleet[0]->getRectangle().left < 0)
			;
		else if (fleet[0]->getRectangle().top < 0) {
			;
		}
		else
			for (auto&& ship : *fleet[0])
				ship->setWeaponsAsActive(true);

		if (fleet[1]->getRectangle().left < 0)
			;
		else if (fleet[1]->getRectangle().top < 0) {
			;
		}
		else
			for (auto&& ship : *fleet[1])
				ship->setWeaponsAsActive(true);




		if (fleet[0]->size() == 0 && fleet[1]->size() == 0) {
			m_CurrentPhase = Phases::four;
			m_Level.clearRects();
		}
	};

	phases.push(phase_three);



	PhaseFunction phase_four;
	phase_four.function = [this](const sf::Time& deltaTime) {

	};

	phases.push(phase_four);


	*/
}


void LevelManagerOne::update(const sf::Time& deltaTime)
{
	updatePhase(deltaTime);

	m_Level.update(deltaTime);
}




void LevelManagerOne::addFleet(EnemyShip::Type type, sf::FloatRect area, sf::Vector2f padding, std::optional<Fleet::PositionType> pos)
{
	Fleet fleet(type, area, padding, false);
	fleet.setWeaponsAsActive(false);

	if (pos.has_value())
		fleet.setPosition(pos.value());

	m_Level.addFleet(std::move(fleet));
}

Fleet* LevelManagerOne::initFleet(EnemyShip::Type type, sf::FloatRect area, sf::Vector2f padding, std::optional<Fleet::PositionType> pos)
{
	Fleet* fleet = new Fleet(type, area, padding, false);
	fleet->setWeaponsAsActive(false);

	if (pos.has_value())
		fleet->setPosition(pos.value());

	return fleet;
}

void LevelManagerOne::debugSpawn()
{
	Fleet::PositionType setPosition = std::make_tuple(X::Middle, Place::Inside, Y::Top, Place::Outside);
	Fleet* fleet = initFleet(EnemyShip::Type::scout,
		sf::FloatRect(0, 0, Configuration::boundaries.x, 400),
		sf::Vector2f(5, 5),
		setPosition);


	auto rect = fleet->getRectangle();
	float length = rect.top;

	fleet->addMovementToQueue({ 0.f, 1.f }, length);

	m_Level.addFleet(std::move(*fleet));
}

void LevelManagerOne::updatePhase(const sf::Time& deltaTime)
{
	//if (!phases.empty()) {
	//	phases.front().function(deltaTime);
	//}


	switch (m_CurrentPhase)
	{
	case Phases::one:		phaseOne(deltaTime);		break;
	case Phases::two:		phaseTwo(deltaTime);		break;
	case Phases::three:		phaseThree(deltaTime);		break;
	case Phases::four:		phaseFour(deltaTime);		break;
	//case Phases::five:		phaseFive(deltaTime);		break;
	//case Phases::six:		phaseSix(deltaTime);			break;
	//case Phases::seven:		phaseSeven(deltaTime);		break;
	//case Phases::eight:		phaseEight(deltaTime);		break;
	//case Phases::nine:		phaseNine(deltaTime);		break;
	default:											break;
	}
}


void LevelManagerOne::phaseOne(const sf::Time&)
{
	static Fleet* fleet = nullptr;
	if (static bool firstTime = true; firstTime) {
		Fleet::PositionType setPosition = std::make_tuple(X::Middle, Place::Inside, Y::Top, Place::Outside);
		addFleet(EnemyShip::Type::scout,
			sf::FloatRect(0, 0, Configuration::boundaries.x, 400),
			sf::Vector2f(5, 5),
			setPosition);


		fleet = m_Level.getFleetPtr(0);


		auto rect = fleet->getRectangle();
		float length = rect.top;

		fleet->addMovementToQueue({ 0.f, 1.f }, length);

		firstTime = false;
		return;
	}

	if (fleet->size() == 0) {
		m_CurrentPhase = Phases::two;
	}
}

void LevelManagerOne::phaseTwo(const sf::Time&)
{
	static Fleet* fleet[2]{nullptr,nullptr};

	if (static bool firstTime = true; firstTime) {
		Fleet::PositionType position1 = std::make_tuple(X::Left, Place::Outside, Y::Top, Place::Inside);
		addFleet(EnemyShip::Type::scout,
			sf::FloatRect(0, 0, Configuration::boundaries.x / 2.f - 100, 400),
			sf::Vector2f(5, 5),
			position1);


		Fleet::PositionType position2 = std::make_tuple(X::Right, Place::Outside, Y::Top, Place::Inside);
		addFleet(EnemyShip::Type::scout,
			sf::FloatRect(0, 0, Configuration::boundaries.x / 2.f - 100, 400),
			sf::Vector2f(5, 5),
			position2);


		fleet[0] = m_Level.getFleetPtr(0);
		fleet[1] = m_Level.getFleetPtr(1);


		auto rect0 = fleet[0]->getRectangle();
		float length = rect0.width;
		fleet[0]->addMovementToQueue({ 1.f, 0.f }, length);
		fleet[1]->addMovementToQueue({ -1.f, 0.f }, length);


		firstTime = false;
		return;
	}



	if (fleet[0]->size() == 0 && fleet[1]->size() == 0){
		m_CurrentPhase = Phases::three;
	}
}



void LevelManagerOne::phaseThree(const sf::Time& deltaTime)
{

	static Fleet* fleet[2]{ nullptr,nullptr };

	if (static bool firstTime = true; firstTime) {
		Fleet::PositionType position1 = std::make_tuple(X::Left, Place::Inside, Y::Top, Place::Outside);
		addFleet(EnemyShip::Type::stealth,
			sf::FloatRect(0, 0, 200, 400),
			sf::Vector2f(5, 5),
			position1);

		Fleet::PositionType position2 = std::make_tuple(X::Right, Place::Inside, Y::Top, Place::Outside);
		addFleet(EnemyShip::Type::stealth,
			sf::FloatRect(0, 0, 200, 400),
			sf::Vector2f(5, 5),
			position2);


		std::vector<sf::Vector2f> wp = { {75, 86},{1850, 906},{80, 866},{930, -144},{1850, 906},{80, 866},{1855, 91} };
		Spline path(wp, 0.01f, true);

		fleet[0] = m_Level.getFleetPtr(0);
		fleet[0]->setPath(path);
		fleet[1] = m_Level.getFleetPtr(1);
		fleet[1]->setPath(path.getMirroredPath(true));
		firstTime = false;
		return;
	}



	if (fleet[0]->size() == 0 && fleet[1]->size() == 0){
		m_CurrentPhase = Phases::four;
	}
}







void LevelManagerOne::phaseFour(const sf::Time&)
{
	m_IsFinished = true;
}
