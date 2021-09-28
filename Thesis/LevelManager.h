#pragma once
#include "Level.h"

class LevelManager
{
protected:
	Level& m_Level;

public:
	explicit LevelManager(Level& level);
	virtual ~LevelManager();


	virtual void update(const sf::Time& deltaTime) = 0;
};
