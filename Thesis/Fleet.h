#pragma once
#include "EnemyShip.h"

class Fleet :
	public sf::Drawable
{
private:
	void draw(sf::RenderTarget& target, sf::RenderStates) const override;
	std::vector<EnemyShip::ptr> m_Fleet;

public:
	
#pragma region custom vector overloads
	EnemyShip::ptr& operator[](std::size_t index);
	const EnemyShip::ptr& operator[](std::size_t index) const;
	void erase(std::size_t index);
	std::vector<EnemyShip::ptr>::iterator begin();
	std::vector<EnemyShip::ptr>::iterator end();
	size_t size() const;
#pragma endregion


	void addFleet(std::vector<EnemyShip::ptr> fleet);
	std::vector<EnemyShip::ptr>& getShips();
	sf::FloatRect getRectangle();



	void update(const sf::Time& deltaTime);

	void move(const sf::Vector2f& moveBy);

	typedef std::unique_ptr<Fleet> ptr;
};