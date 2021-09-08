#include "pch.h"
#include "Level.h"
#include "ScoutEnemyShip.h"

void Level::draw(sf::RenderTarget& target, sf::RenderStates) const
{
	for (auto&& entity : m_Entities) {
		target.draw(*entity);

	}
}

Level::Level(sf::RenderWindow& window)
	:m_Window(window)
{
	sf::FloatRect rect(0, 0, m_Window.getSize().x, m_Window.getSize().y / 3.f);

	populateAreaWithEnemies(m_Entities, EnemyShips::scout, rect, sf::Vector2f(20.f,10.f));
}

Level::~Level()
{
}

void Level::update(const sf::Time& deltaTime)
{
	for (auto&& entity : m_Entities)
		entity->update(deltaTime);


}

void Level::populateAreaWithEnemies(std::vector<Entity::ptr>& container, EnemyShips enemyShip, sf::FloatRect area, sf::Vector2f padding)
{
	sf::Vector2f size;
	switch (enemyShip) {
		case EnemyShips::minigun:
			size = (sf::Vector2f)Configuration::textures_ships.get(Configuration::TexturesShips::enemy_ship_minigun).getSize();
		break;
		case EnemyShips::support:
			size = (sf::Vector2f)Configuration::textures_ships.get(Configuration::TexturesShips::enemy_ship_support).getSize();
		break;
		case EnemyShips::beam:
			size = (sf::Vector2f)Configuration::textures_ships.get(Configuration::TexturesShips::enemy_ship_beam).getSize();
		break;
		case EnemyShips::rocket:
			size = (sf::Vector2f)Configuration::textures_ships.get(Configuration::TexturesShips::enemy_ship_rocket).getSize();
		break;
		case EnemyShips::scout:
			size = (sf::Vector2f)Configuration::textures_ships.get(Configuration::TexturesShips::enemy_ship_scout).getSize();
		break;
		case EnemyShips::tank:
			size = (sf::Vector2f)Configuration::textures_ships.get(Configuration::TexturesShips::enemy_ship_tank).getSize();
		break;
		case EnemyShips::scout_v2:
			size = (sf::Vector2f)Configuration::textures_ships.get(Configuration::TexturesShips::enemy_ship_scout_v2).getSize();
		break;
		case EnemyShips::stealth:
			size = (sf::Vector2f)Configuration::textures_ships.get(Configuration::TexturesShips::enemy_ship_stealth).getSize();
		break;
		case EnemyShips::boss:
			size = (sf::Vector2f)Configuration::textures_ships.get(Configuration::TexturesShips::enemy_ship_boss).getSize();
		break;
	}

	int num_x = area.width / (size.x + padding.x);
	int num_y = area.height / (size.y + padding.y);

	sf::Vector2f mid_padding;
	mid_padding.x = (area.width - static_cast<float>(num_x) * size.x) / static_cast<float>(num_x);
	mid_padding.y = (area.height- static_cast<float>(num_y) * size.y) / static_cast<float>(num_y);

	for(int i = 0; i < num_x; i++)
		for (int j = 0; j < num_y; j++) {
			
			auto enemy = createEnemy(EnemyShips::scout);

			sf::Vector2f pos(area.left + i* size.x, area.top + j * size.y);

			// Origin in the middle, so move the pos
			pos += size / 2.f;

			pos.x += (i + 1) * mid_padding.x;
			pos.y += (j + 1) * mid_padding.y;


			enemy->setPosition(pos);

			m_Entities.push_back(std::move(enemy));
		}

	puts(std::to_string(container.size()).c_str());
}

Entity::ptr Level::createEnemy(EnemyShips ship)
{
	Entity::ptr enemy;
	switch (ship) {
	case EnemyShips::minigun:
		enemy = createEnemyMinigun();
		break;
	case EnemyShips::support:
		enemy = createEnemySupport();
		break;
	case EnemyShips::beam:
		enemy = createEnemyBeam();
		break;
	case EnemyShips::rocket:
		enemy = createEnemyRocket();
		break;
	case EnemyShips::scout:
		enemy = createEnemyScout();
		break;
	case EnemyShips::tank:
		enemy = createEnemyTank();
		break;
	case EnemyShips::scout_v2:
		enemy = createEnemyScoutV2();
		break;
	case EnemyShips::stealth:
		enemy = createEnemyStealth();
		break;
	case EnemyShips::boss:
		enemy = createEnemyBoss();
		break;
	}

	return std::move(enemy);
}

Entity::ptr Level::createEnemyMinigun()
{
	return Entity::ptr();
}

Entity::ptr Level::createEnemySupport()
{
	return Entity::ptr();
}

Entity::ptr Level::createEnemyBeam()
{
	return Entity::ptr();
}

Entity::ptr Level::createEnemyRocket()
{
	return Entity::ptr();
}

Entity::ptr Level::createEnemyScout()
{
	std::unique_ptr<ScoutEnemyShip> enemy(new ScoutEnemyShip(Configuration::TexturesShips::enemy_ship_scout));
	

	return std::move(enemy);
}

Entity::ptr Level::createEnemyTank()
{
	return Entity::ptr();
}

Entity::ptr Level::createEnemyScoutV2()
{
	return Entity::ptr();
}

Entity::ptr Level::createEnemyStealth()
{
	return Entity::ptr();
}

Entity::ptr Level::createEnemyBoss()
{
	return Entity::ptr();
}

