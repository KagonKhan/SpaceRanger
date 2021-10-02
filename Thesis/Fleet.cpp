#include "pch.h"
#include "Fleet.h"
#include "Level.h"

void Fleet::draw(sf::RenderTarget& target, sf::RenderStates) const
{
	for (auto&& ship : m_Ships)
		target.draw(*ship);
}

void Fleet::addMovementToQueue(sf::Vector2f dir, float length)
{
	Helpers::normalize(dir);

	m_MoveQueue.first.emplace( std::pair{ dir,length });
}



Fleet::Fleet(Fleet&& other) noexcept
: m_Ships(std::move(other.m_Ships)), m_Path(std::move(other.m_Path))
{}

Fleet& Fleet::operator=(Fleet&& other)noexcept
{
	m_Ships = std::move(other.m_Ships);
	m_Path = std::move(other.m_Path);
	return *this;
}

Fleet::Fleet(std::vector<EnemyShip::ptr> fleet)
{
	m_Ships = std::move(fleet);
}

Fleet::Fleet(EnemyShip::Type type, sf::FloatRect area, sf::Vector2f padding)
{

	sf::Vector2f size = EnemyShip::create(type)->getSize();

	int num_x = static_cast<int>((area.width) / (size.x + padding.x));
	int num_y = static_cast<int>((area.height) / (size.y + padding.y));


	sf::Vector2f mid_padding;
	mid_padding.x = (area.width - static_cast<float>(num_x) * size.x) / static_cast<float>(num_x);
	mid_padding.y = (area.height - static_cast<float>(num_y) * size.y) / static_cast<float>(num_y);

	//m_Ships.resize(num_x * num_y);

	for (int i = 0; i < num_x; i++)
		for (int j = 0; j < num_y; j++) {

			auto enemy = EnemyShip::create(type);

			sf::Vector2f pos(area.left + i * size.x, area.top + j * size.y);

			// Origin in the middle, so move the pos
			pos += size / 2.f;

			pos.x += (static_cast<float>(i) + 1) * mid_padding.x;
			pos.x -= mid_padding.x / 2.f;
			pos.y += (static_cast<float>(j) + 1) * mid_padding.y;

			enemy->setPosition(pos);

			m_Ships.push_back(std::move(enemy));
		}


	auto rect = getRectangle();
	sf::Vector2f moveTo(area.left - rect.left, area.top - rect.top);
	move(moveTo);


	m_MoveQueue.second = true;
}


void Fleet::setPosition(PositionType pos)
{
	using namespace pos;


	auto rect = getRectangle();
	sf::Vector2f moveTo00(-rect.left, -rect.top);
	move(moveTo00);


	auto [X, Xplace, Y, Yplace] = pos;
	sf::Vector2f moveBy;

	sf::Vector2f m_WinSize = Configuration::boundaries;

	switch (X) {
	case X::Left:	moveBy.x += -rect.width + ((Xplace == Place::Inside) ? +rect.width : 0);	break;										break;
	case X::Middle:	moveBy.x += (m_WinSize.x - rect.width) / 2.f;								break;
	case X::Right:	moveBy.x += m_WinSize. x + ((Xplace == Place::Inside) ? -rect.width : 0);	break;
	default:																					break;
	}

	
	switch (Y) {
	case Y::Top:	moveBy.y += ((Yplace == Place::Inside) ? 0 : -rect.height);					break;
	case Y::Middle:	moveBy.y += (m_WinSize.y - rect.height) / 2.f;								break;
	case Y::Bottom:	moveBy.y += m_WinSize.y + ((Yplace == Place::Inside) ? -rect.height : 0);	break;
	default:																					break;
	}	



	move(moveBy);
}


void Fleet::setPath(const std::vector<sf::Vector2f>& waypoints)
{
	m_Path.emplace(waypoints, 0.01, true);

	for (auto&& ship : m_Ships) {
		ship->setPath(m_Path.value());
	}
}

void Fleet::setPath(Spline path)
{
	m_Path = path;

	for (auto&& ship : m_Ships) {
		ship->setPath(m_Path.value());
	}
}



// does not work for now - when enemy is destroyed i teleport it to-99999-999999
sf::FloatRect Fleet::getRectangle() const
{
	float min_x{ std::numeric_limits<float>::max() };
	float min_y{ std::numeric_limits<float>::max() };

	float max_x{ std::numeric_limits<float>::min() };
	float max_y{ std::numeric_limits<float>::min() };

	for (auto&& ship : m_Ships) {
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




void Fleet::update(const sf::Time& deltaTime)
{
	for (auto&& ship : m_Ships) {
		ship->update(deltaTime);
	}

	static auto& [queue, ready] = m_MoveQueue;
	if (!queue.empty()) {
		if (ready) {
			for (auto&& ship : m_Ships) {
				ship->setMovement(queue.front());
			}
			ready = false;
			queue.pop();
		}

	}
	

	for (auto&& ship : m_Ships)
		if (ship->hasMoveCommand() == false)
			ready = true;

}

void Fleet::move(const sf::Vector2f& moveBy)
{
	for (auto&& ship : m_Ships)
		ship->move(moveBy);
}

void Fleet::setWeaponsAsActive(bool active)
{
	for (auto&& ship : m_Ships)
		ship->setWeaponsAsActive(active);
}




