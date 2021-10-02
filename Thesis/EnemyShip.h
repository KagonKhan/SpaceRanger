#pragma once
#include "Ship.h"
#include "Spline.h"

struct Movement
{
	std::pair<sf::Vector2f, float> move;
};

class EnemyShip :
	public Ship
{

private:
	sf::Vector2f m_Target;
	bool m_GetNextPoint{ true };

protected:
	std::optional<Spline> m_Path;
	std::optional<Movement> m_Move;
	void updateMovement(const sf::Time& deltaTime) override;
	void followPath( const sf::Time& deltaTime);
	void followDir(const sf::Time& deltaTime);

	void setRotation(float angle )					{	m_Sprite.setRotation(angle);	}

public:
	using ptr = std::unique_ptr<EnemyShip>;
	enum class Type {
		minigun, support, beam, rocket, scout, tank, scout_v2, stealth, boss,
	};



	EnemyShip(float maxHp, Configuration::TexturesShips tex_id);

	void setTargetPos(sf::Vector2f pos);

	void setMovement(Movement move);
	bool isMoving() const;
	bool hasValue()const { return m_Move.has_value(); }

	static ptr create(Type ship);


	void setPath(const std::optional<Spline>& path) {		m_Path = path;		}
};