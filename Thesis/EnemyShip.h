#pragma once
#include "Ship.h"
#include "Spline.h"


class EnemyShip :
	public Ship
{
	void draw(sf::RenderTarget& target, sf::RenderStates) const override;
protected:
	std::optional<Spline> m_Path;
	void updateMovement(const sf::Time& deltaTime) override;
	void followPath(const sf::Time& deltaTime);

	void setRotation(float angle);

public:
	EnemyShip(float maxHp, Configuration::TexturesShips tex_id);
	virtual ~EnemyShip();

	void setPath(const std::optional<Spline>& path);



	typedef std::unique_ptr<EnemyShip> ptr;
};