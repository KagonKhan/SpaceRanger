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
	: Ship(maxHp, tex_id), m_Path(std::nullopt)
{
	srand(reinterpret_cast<unsigned int>(this));
}

void EnemyShip::setTargetPos(sf::Vector2f pos)
{ 
	m_Target = pos;
}



void EnemyShip::updateMovement(const sf::Time& deltaTime)
{
	if (m_Path.has_value())
		followPath(deltaTime);
	else if (m_Move.has_value())
		followDir(deltaTime);



}

void EnemyShip::followPath( const sf::Time& deltaTime)
{
	if (m_GetNextPoint) {
		m_Target = m_Path.value().getNextPoint();
		m_GetNextPoint = false;


		//std::cout << "\nangle: " << m_Path.value().getAngle();
	}


	float length = Helpers::getLength(m_Target - m_Position);
	m_Direction = Helpers::normalize(m_Target - m_Position);

	//setRotation(m_Path.value().getAngle() - 90.f);

	if (length < 15.f)
		m_GetNextPoint = true;


	sf::Vector2f moveBy = m_Direction * m_Speed * deltaTime.asSeconds();
	move(moveBy);
}

void EnemyShip::followDir(const sf::Time& deltaTime)
{
	auto& [dir, length] = m_Move.value().move;
	m_Direction = Helpers::normalize(std::as_const(dir));

	sf::Vector2f moveBy = dir * m_Speed * deltaTime.asSeconds();

	move(moveBy);

	length -= Helpers::getLength(moveBy);

	if (length < 5.f)
		m_Move.reset();
}

void EnemyShip::setMovement(Movement move)
{
	m_Move.emplace(move);
}

bool EnemyShip::isMoving() const
{
	return Helpers::getLength(m_Direction) > 0;
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
