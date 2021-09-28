#include "pch.h"
#include "EnemyShip.h"

EnemyShip::EnemyShip(float maxHp, Configuration::TexturesShips tex_id)
	: Ship(maxHp, tex_id), m_Path(std::nullopt)
{
	srand(reinterpret_cast<unsigned int>(this));
}

EnemyShip::~EnemyShip()
{
}

void EnemyShip::setPath(const std::optional<Spline>& path)
{
	m_Path = path;




}

void EnemyShip::setRotation(float angle)
{
	m_Sprite.setRotation(angle);
}



void EnemyShip::draw(sf::RenderTarget& target, sf::RenderStates) const
{
	target.draw(m_Sprite);

	for (auto&& weapon : m_Weapons)
		target.draw(*weapon);

	if(m_Path.has_value())
	Helpers::drawPath(target, m_Path.value());
}

void EnemyShip::updateMovement(const sf::Time& deltaTime)
{


	if (m_Path.has_value())
		followPath(deltaTime);
}

void EnemyShip::followPath(const sf::Time& deltaTime)
{




	static sf::Vector2f target;
	static bool getNextPoint = true;
	if (getNextPoint) {
		target = m_Path.value().getNextPoint();
		getNextPoint = false;


		//std::cout << "\nangle: " << m_Path.value().getAngle();
	}
	float length = Helpers::getLength(target - m_Position);
	m_Direction = Helpers::normalize((target - m_Position));

	setRotation(m_Path.value().getAngle() - 90.f);

	if (length < 15.f)
		getNextPoint = true;

	m_Position += m_Direction * 200.f * deltaTime.asSeconds();

}
