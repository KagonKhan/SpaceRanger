#pragma once
#include "Entity.h"
#include "ActionTarget.h"
#include "Ship.h"

class Player :
	public Ship,
	protected ActionTarget<int>
{
private:
	sf::Vector2f m_Boundaries;
	/* Different types of weapons */
	
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override final;

public:
	Player(const Player&) = delete;
	Player operator=(const Player&) = delete;

	Player(Configuration::Textures tex_id, const sf::Vector2f& boundaries);

	

	void update(const sf::Time& deltaTime);
};

