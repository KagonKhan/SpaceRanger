#pragma once
#include "Ship.h"
#include "Spline.h"


class EnemyShip :
	public Ship
{
protected:
	std::optional<Spline> m_Path;
	void updateMovement(const sf::Time& deltaTime) override;
	void followPath(const sf::Time& deltaTime);


	void setRotation(float angle )					{	m_Sprite.setRotation(angle);	}

public:
	EnemyShip(float maxHp, Configuration::TexturesShips tex_id);




	void setPath(const std::optional<Spline>& path) {		m_Path = path;		}

	using ptr = std::unique_ptr<EnemyShip>;
};