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
	auto& operator[](std::size_t index) {
		return m_Fleet[index];
	}
	const EnemyShip::ptr& operator[](std::size_t index) const {
		return m_Fleet[index];
	}
	void erase(std::size_t index) {
		m_Fleet.erase(m_Fleet.begin() + index);
	}
	auto begin() {
		return m_Fleet.begin();
	}
	auto end() {
		return m_Fleet.end();
	}
	auto data() {
		return m_Fleet[0].get();
	}
	auto cbegin() const {
		return m_Fleet.begin();
	}
	auto cend() const	{
		return m_Fleet.end();
	}
	auto begin() const	{
		return m_Fleet.begin();
	}
	auto end() const	{
		return m_Fleet.end();	
	}
	size_t size() const {
		return m_Fleet.size();
	}
#pragma endregion


	void addFleet(std::vector<EnemyShip::ptr> fleet);
	std::vector<EnemyShip::ptr>& getShips();
	sf::FloatRect getRectangle();
	sf::Vector2f getSize();


	void update(const sf::Time& deltaTime);

	void move(const sf::Vector2f& moveBy);

	typedef std::unique_ptr<Fleet> ptr;
};