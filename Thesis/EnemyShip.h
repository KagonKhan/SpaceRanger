#pragma once
#include "Ship.h"
#include "Spline.h"

struct MoveCommand
{
	std::pair<sf::Vector2f, float> move;
};

class EnemyShip :
	public Ship
{
protected:
	std::optional<std::pair<Spline, bool>>	m_Path{ std::nullopt };
	std::optional<MoveCommand>				m_Move{ std::nullopt };


	void updateMovement(const sf::Time& deltaTime) override;
	void followPath( const sf::Time& deltaTime);
	void followDir(const sf::Time& deltaTime);

public:
	EnemyShip(float maxHp, Configuration::TexturesShips tex_id);

	using ptr = std::unique_ptr<EnemyShip>;
	enum class Type {
		minigun, support, beam, rocket, scout, tank, scout_v2, stealth, boss,
	};	static ptr create(Type ship);


	bool hasMoveCommand() const						{		return m_Move.has_value();		}
	void setRotation(float angle )					{		m_Sprite.setRotation(angle);	}
	void setMovement(MoveCommand move)				{		m_Move.emplace(move);			}
	void setPath(const Spline& path)				{		m_Path.emplace(path, true);		}
};