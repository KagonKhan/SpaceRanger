#include "pch.h"
#include "Fleet.h"

void Fleet::draw(sf::RenderTarget& target, sf::RenderStates) const
{
	for (auto&& ship : m_Fleet)
		target.draw(*ship);
}


void Fleet::addFleet(std::vector<EnemyShip::ptr> fleet)
{
	m_Fleet = std::move(fleet);
}

std::vector<EnemyShip::ptr>& Fleet::getShips()
{
	return m_Fleet;
}
// does not work for now - when enemy is destroyed i teleport it to-99999-999999
sf::FloatRect Fleet::getRectangle()
{
	float max_x{ std::numeric_limits<float>::min() }, min_x{ std::numeric_limits<float>::max() };
	float max_y{ std::numeric_limits<float>::min() }, min_y{ std::numeric_limits<float>::max() };

	for (auto&& ship : m_Fleet) {
		const sf::Vector2f curr_ship_size(ship->getSize() / 2.f);
		const sf::Vector2f curr_ship_pos(ship->getPosition());

		if (max_x < curr_ship_pos.x + curr_ship_size.x) max_x = curr_ship_pos.x + curr_ship_size.x;
		if (max_y < curr_ship_pos.y + curr_ship_size.y)	max_y = curr_ship_pos.y + curr_ship_size.y;

		if (min_x > curr_ship_pos.x - curr_ship_size.x)	min_x = curr_ship_pos.x - curr_ship_size.x;
		if (min_y > curr_ship_pos.y - curr_ship_size.y)	min_y = curr_ship_pos.y - curr_ship_size.y;
	}

	sf::Vector2f pos(min_x, min_y);
	sf::Vector2f size(sf::Vector2f(max_x, max_y) - pos);

	return sf::FloatRect(pos,size);
}

sf::Vector2f Fleet::getSize()
{
	return sf::Vector2f(getRectangle().width, getRectangle().height);
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
