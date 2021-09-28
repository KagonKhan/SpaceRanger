#pragma once
#include "Ship.h"
#include "Spline.h"


class EnemyShip :
	public Ship
{

private:
	sf::Vector2f m_Target;
	bool m_GetNextPoint{ true };

protected:
	std::optional<Spline> m_Path;
	void updateMovement(const sf::Time& deltaTime) override;
	void followPath( const sf::Time& deltaTime);


	void setRotation(float angle )					{	m_Sprite.setRotation(angle);	}

public:
	EnemyShip(float maxHp, Configuration::TexturesShips tex_id);

	void setTargetPos(sf::Vector2f pos);


	void setPath(const std::optional<Spline>& path) {		m_Path = path;		}

	using ptr = std::unique_ptr<EnemyShip>;
};