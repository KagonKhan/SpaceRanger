#include "pch.h"
#include "EnemyShip.h"


#include "BeamShip.h"
#include "BossEnemyShip.h"
#include "MinigunShip.h"
#include "RocketShip.h"
#include "ScoutEnemyShip.h"
#include "ScoutShipV2.h"
#include "StealthShip.h"
#include "SupportShip.h"
#include "TankShip.h"

EnemyShip::EnemyShip(float maxHp, Configuration::TexturesShips tex_id)
	: Ship(maxHp, tex_id)
{}



void EnemyShip::draw(sf::RenderTarget& target, sf::RenderStates) const
{

	target.draw(m_Sprite);

	for (auto&& weapon : m_Weapons)
		target.draw(*weapon);

}


void EnemyShip::updateMovement(const sf::Time& deltaTime)
{
	if (m_OnDestroy.isMarkedForDeletion()) {
		m_Direction = sf::Vector2f(0, 0);
		return;
	}

	if (m_Path.has_value())
		followPath(deltaTime);
	else if (m_Move.has_value())
		followDir(deltaTime);
}

void EnemyShip::followPath( const sf::Time& deltaTime)
{
	auto& [path, getNextPoint] = m_Path.value();
	sf::Vector2f target;

	if (getNextPoint) {
		target = path.getNextPoint();
		getNextPoint = false;
	}
	else {
		target = path.getCurrent();
	}

	//setRotation(m_Path.value().getAngle() - 90.f);

	m_Direction	= Helpers::normalize(target - m_Position);
	move(m_Direction * m_Speed * deltaTime.asSeconds());

	if (Helpers::getLength(target - m_Position) < (m_Speed / 20.f))
		getNextPoint = true;
}

void EnemyShip::followDir(const sf::Time& deltaTime)
{
	auto& [dir, length] = m_Move.value().move;
	m_Direction = Helpers::normalize(std::as_const(dir));

	sf::Vector2f moveBy = dir * m_Speed * deltaTime.asSeconds();
	move(moveBy);

	length -= Helpers::getLength(moveBy);
	if (length < 5.f) {
		m_Move.reset();
		m_Direction = sf::Vector2f(0, 0);
	}
}


EnemyShip::ptr EnemyShip::create(Type ship)
{
	EnemyShip::ptr enemy;

	switch (ship) {
	case Type::minigun:			enemy = std::make_unique<MinigunShip>();	break;
	case Type::support:			enemy = std::make_unique<SupportShip>();	break;
	case Type::beam:			enemy = std::make_unique<BeamShip>();		break;
	case Type::rocket:			enemy = std::make_unique<RocketShip>();		break;
	case Type::scout:			enemy = std::make_unique<ScoutEnemyShip>();	break;
	case Type::tank:			enemy = std::make_unique<TankShip>();		break;
	case Type::scout_v2:		enemy = std::make_unique<ScoutShipV2>();	break;
	case Type::stealth:			enemy = std::make_unique<StealthShip>();	break;
	case Type::boss:			enemy = std::make_unique<BossEnemyShip>();	break;
	default:																break;
	}

	return std::move(enemy);
}

bool EnemyShip::shouldBeDeleted()
{
	if (m_OnDestroy.isMarkedForDeletion())
		return true;

	if (getHP() <= 0) {
		m_OnDestroy.start();
		return true;
	}

	return false;
}
