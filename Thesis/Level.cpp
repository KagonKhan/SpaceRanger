#include "pch.h"
#include "Level.h"


#include "Ammunition.h"
#include "PlayerShip.h"


void Level::draw( sf::RenderTarget& target, sf::RenderStates ) const
{
	for (auto&& fleet : m_Enemies) 
		target.draw(fleet);
	
	for (auto&& fleet : m_rects)
		target.draw(fleet);

}

Level::Level( sf::RenderWindow& window, PlayerShip& player )
	:m_Window(window), m_Player(player)
{

}


void Level::addRect()
{
	auto rect = m_Enemies.back().getRectangle();
	sf::RectangleShape shape(sf::Vector2f(rect.width, rect.height));
	shape.setPosition(rect.left, rect.height);
	shape.setFillColor(sf::Color::Transparent);

	shape.setOutlineColor(sf::Color::White);
	shape.setOutlineThickness(2.f);

	m_rects.push_back(shape);
}



void Level::addFleet(std::vector<EnemyShip::ptr> fleet)
{
	m_Enemies.emplace_back(std::move(fleet));
	addRect();
}

void Level::addFleet(Fleet fleet)
{
	m_Enemies.push_back(std::move(fleet));
	addRect();
}



void Level::update(const sf::Time& deltaTime)
{	
	updateEnemies(deltaTime);
	checkCollisions();


	for (int i = 0; i < m_Enemies.size(); ++i) {
		auto rect = m_Enemies[i].getRectangle();
		m_rects[i].setPosition(rect.left, rect.top);
		m_rects[i].setSize(sf::Vector2f(rect.width, rect.height));
	}
}

void Level::updateEnemies(const sf::Time& deltaTime)
{
	for (auto&& fleet : m_Enemies)
		fleet.update(deltaTime);

	for (auto&& ship : m_EnemiesForDeletion)
		ship->update(deltaTime);
}

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
	for (auto&& fleet : m_Enemies)
		for (auto&& enemy : fleet.getShips())
			if (Ship* ptr = dynamic_cast<Ship*>(enemy.get()); ptr)
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
		for (auto&& fleet : m_Enemies) 
			for (auto&& enemy : fleet.getShips())
				if (Ship* ptr = dynamic_cast<Ship*>(enemy.get()); ptr != nullptr)
					if (Collision::PixelPerfectTest(enemy->getSprite(), ammo->getSprite(), 253U)) 
						enemy->receiveDamage(ammo->dealDamage());

				
}

void Level::checkForDeletion()
{
	for (size_t fleet_num = 0; fleet_num < m_Enemies.size(); ++fleet_num)
		for(size_t ship_num = 0; ship_num < m_Enemies[fleet_num].size(); ++ship_num)
			if (m_Enemies[fleet_num][ship_num]->shouldBeDeleted()) {
				m_EnemiesForDeletion.push_back(std::move(m_Enemies[fleet_num][ship_num]));
				m_Enemies[fleet_num].erase(ship_num--);
			}
	



	for (size_t ship_num = 0; ship_num < m_EnemiesForDeletion.size(); ++ship_num)
		if (m_EnemiesForDeletion[ship_num]->shouldBeDeleted() && m_EnemiesForDeletion[ship_num]->canBeDeleted())
			m_EnemiesForDeletion.erase(m_EnemiesForDeletion.begin() + ship_num--);
	



	// TODO: check if this is necessary - do I have to delete an empty subvector or is it automagically
	for (size_t i = 0; i < m_Enemies.size(); ++i) 
		if (m_Enemies[i].size() == 0)
			m_Enemies.erase(m_Enemies.begin() + i--);
	
}
