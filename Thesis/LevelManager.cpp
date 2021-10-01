#include "pch.h"
#include "LevelManager.h"

LevelManager::LevelManager(Level& level)
	: m_Level(level)
{
	m_WinSize = (sf::Vector2f)level.getWindow().getSize();
}

LevelManager::~LevelManager()
{  
}
