#pragma once
#include "Entity.h"
#include "ActionTarget.h"
class Player :
	public Ship,
	protected ActionTarget<int>
{
private:
	sf::Vector2f m_Boundaries;
	/* Different types of weapons */

public:
	Player(const Player&) = delete;
	Player operator=(const Player&) = delete;

	Player(Configuration::Textures tex_id, const sf::Vector2f& boundaries);
};

