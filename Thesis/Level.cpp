#include "pch.h"
#include "Level.h"
#include "BeamShip.h"
#include "BossEnemyShip.h"
#include "MinigunShip.h"
#include "RocketShip.h"
#include "ScoutEnemyShip.h"
#include "ScoutShipV2.h"
#include "StealthShip.h"
#include "SupportShip.h"
#include "TankShip.h"

#include "Ammunition.h"
#include "PlayerShip.h"
void Level::draw(sf::RenderTarget& target, sf::RenderStates) const
{
	for (auto&& entity : m_Enemies) {
		target.draw(*entity);

	}
}

Level::Level(sf::RenderWindow& window, PlayerShip& player)
	:m_Window(window), m_Player(player)
{

}

Level::~Level()
{
}

void Level::update(const sf::Time& deltaTime)
{
	checkCollisions();
	static int type = 7;
	for (auto&& entity : m_Enemies) {
		entity->update(deltaTime);
	}
	if (m_Enemies.empty()) {
		sf::FloatRect rect(0, 0, m_Window.getSize().x/3, m_Window.getSize().y /3);
		populateAreaWithEnemies(m_Enemies, EnemyShips(type), rect, sf::Vector2f(20.f, 10.f));
		++type;

		type %= 9;
	}
}


#pragma region INIT/ENEMY
void Level::populateAreaWithEnemies(std::vector<EnemyShip::ptr>& container, EnemyShips enemyShip, sf::FloatRect area, sf::Vector2f padding)
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
			
			auto enemy = createEnemy(enemyShip);

			sf::Vector2f pos(area.left + i* size.x, area.top + j * size.y);

			// Origin in the middle, so move the pos
			pos += size / 2.f;

			pos.x += (i + 1) * mid_padding.x;
			pos.y += (j + 1) * mid_padding.y;

			enemy->setPosition(pos);

			m_Enemies.push_back(std::move(enemy));
		}
}

EnemyShip::ptr Level::createEnemy(EnemyShips ship)
{
	EnemyShip::ptr enemy;

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

EnemyShip::ptr Level::createEnemyMinigun()
{
	std::unique_ptr<MinigunShip> enemy(new MinigunShip(Configuration::TexturesShips::enemy_ship_minigun));
	return std::move(enemy);
}
EnemyShip::ptr Level::createEnemySupport()
{
	std::unique_ptr<SupportShip> enemy(new SupportShip(Configuration::TexturesShips::enemy_ship_support));
	return std::move(enemy);
}
EnemyShip::ptr Level::createEnemyBeam()
{
	std::unique_ptr<BeamShip> enemy(new BeamShip(Configuration::TexturesShips::enemy_ship_beam));
	return std::move(enemy);
}
EnemyShip::ptr Level::createEnemyRocket()
{
	std::unique_ptr<RocketShip> enemy(new RocketShip(Configuration::TexturesShips::enemy_ship_rocket));
	return std::move(enemy);
}
EnemyShip::ptr Level::createEnemyScout()
{
	std::unique_ptr<ScoutEnemyShip> enemy(new ScoutEnemyShip(Configuration::TexturesShips::enemy_ship_scout));
	return std::move(enemy);
}
EnemyShip::ptr Level::createEnemyTank()
{
	std::unique_ptr<TankShip> enemy(new TankShip(Configuration::TexturesShips::enemy_ship_tank));
	return std::move(enemy);
}
EnemyShip::ptr Level::createEnemyScoutV2()
{
	std::unique_ptr<ScoutShipV2> enemy(new ScoutShipV2(Configuration::TexturesShips::enemy_ship_scout_v2));
	return std::move(enemy);
}
EnemyShip::ptr Level::createEnemyStealth()
{
	std::unique_ptr<StealthShip> enemy(new StealthShip(Configuration::TexturesShips::enemy_ship_stealth));
	return std::move(enemy);
}
EnemyShip::ptr Level::createEnemyBoss()
{
	std::unique_ptr<BossEnemyShip> enemy(new BossEnemyShip(Configuration::TexturesShips::enemy_ship_boss));
	return std::move(enemy);
}

#pragma endregion


void Level::checkCollisions()
{
	checkEnemyCollisions();
	checkPlayerCollisions();
	checkForDeletion();
}
// Enemy hit player
void Level::checkPlayerCollisions()
{
	std::vector<Ammunition*> ammunition;
	for (auto&& entity : m_Enemies) 
		if (Ship* ptr = dynamic_cast<Ship*>(entity.get()); ptr)
			ammunition.insert(ammunition.begin(), ptr->getShots().begin(), ptr->getShots().end());
	
	
	for (auto&& ammo : ammunition)
		if (Collision::PixelPerfectTest(m_Player.getSprite(), ammo->getSprite(), 253U)) {
			m_Player.receiveDamage(ammo->dealDamage() * 0.f);
		}
}
// Player hit enemy
void Level::checkEnemyCollisions()
{
	std::vector<Ammunition*> ammunition;
	ammunition.insert(ammunition.begin(), m_Player.getShots().begin(), m_Player.getShots().end());

	for(auto&& ammo : ammunition)
		for (auto&& enemy : m_Enemies)
			if (Ship* ptr = dynamic_cast<Ship*>(enemy.get()); ptr != nullptr)
				if (Collision::PixelPerfectTest(enemy->getSprite(), ammo->getSprite(), 253U)) {
					enemy->receiveDamage(ammo->dealDamage());
					if (enemy->getCurrentHP() <= 0) {
						enemy->setPosition(-99999, -99999);
						enemy->markForDeletion();
					}

				}
}

void Level::checkForDeletion()
{
	for (unsigned int i = 0; i < m_Enemies.size(); ++i) {
		if (m_Enemies[i]->shouldBeDeleted() && m_Enemies[i]->canBeDeleted())
			m_Enemies.erase(m_Enemies.begin() + i);
	}
}

