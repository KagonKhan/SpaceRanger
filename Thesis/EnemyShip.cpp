#include "pch.h"
#include "EnemyShip.h"

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

	m_Position += m_Direction * 600.f * deltaTime.asSeconds();
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

	setRotation(m_Path.value().getAngle() - 90.f);

	if (length < 15.f)
		m_GetNextPoint = true;

}
