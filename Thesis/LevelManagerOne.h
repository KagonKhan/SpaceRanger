#pragma once

#include "LevelManager.h"


class LevelManagerOne :
	public LevelManager
{
private:

	enum class Phases {
		one, two, three, four, five, six, seven, eight, nine
	};
	Phases m_CurrentPhase;

	void initFleet(Level::EnemyShips type, sf::FloatRect area, sf::Vector2f padding);


	/* could hold these in an array */
	void updatePhase(const sf::Time& deltaTime);
		void phaseOne(const sf::Time& deltaTime);
		void phaseTwo(const sf::Time& deltaTime);
		void phaseThree(const sf::Time& deltaTime);
		void phaseFour(const sf::Time& deltaTime);
		void phaseFive(const sf::Time& deltaTime);
		void phaseSix(const sf::Time& deltaTime);
		void phaseSeven(const sf::Time& deltaTime);
		void phaseEight(const sf::Time& deltaTime);
		void phaseNine(const sf::Time& deltaTime);


public:
	explicit LevelManagerOne(Level& level);

	void update(const sf::Time& deltaTime) override;
};