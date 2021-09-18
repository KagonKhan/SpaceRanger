#include "pch.h"
#include "Fleet.h"

void Fleet::draw(sf::RenderTarget& target, sf::RenderStates) const
{
	for (auto&& ship : m_Fleet)
		target.draw(*ship);
}

EnemyShip::ptr& Fleet::operator[](std::size_t index)
{
	return m_Fleet[index];
}

const EnemyShip::ptr& Fleet::operator[](std::size_t index) const
{
	return m_Fleet[index];
}

void Fleet::erase(std::size_t index)
{
	m_Fleet.erase(m_Fleet.begin() + index);
}

std::vector<EnemyShip::ptr>::iterator Fleet::begin()
{
	return m_Fleet.begin();
}

std::vector<EnemyShip::ptr>::iterator Fleet::end()
{
	return m_Fleet.end();
}

void Fleet::addFleet(std::vector<EnemyShip::ptr> fleet)
{
	m_Fleet = std::move(fleet);
}

std::vector<EnemyShip::ptr>& Fleet::getShips()
{
	return m_Fleet;
}

sf::FloatRect Fleet::getRectangle()
{
	float minX = 999999, minY = 999999, maxX = -999999, maxY = -999999;
	for (auto&& ship : m_Fleet) {
		auto pos = ship->getPosition();
		auto size = ship->getSize();

		if (pos.x - size.x < minX)
			minX = pos.x - size.x;
		if (pos.y - size.y < minY)
			minY = pos.y - size.y;

		if (pos.x + size.x > maxX)
			maxX = pos.x + size.x;
		if (pos.y + size.y > maxY)
			maxY = pos.y + size.y;
	}

	return sf::FloatRect(minX, minY, maxX - minX, maxY - minY);
}

size_t Fleet::size() const
{
	return m_Fleet.size();
}

void Fleet::update(const sf::Time& deltaTime)
{
	for (auto&& ship : m_Fleet)
		ship->update(deltaTime);
}

void Fleet::move(const sf::Vector2f& moveBy)
{
	for (auto&& ship : m_Fleet)
		ship->setPosition(ship->getPosition() + moveBy);
}
