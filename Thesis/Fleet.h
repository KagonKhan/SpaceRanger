#pragma once
#include "EnemyShip.h"


class Fleet :
	public sf::Drawable
{
private:
	void draw(sf::RenderTarget& target, sf::RenderStates) const override;
	std::vector<EnemyShip::ptr> m_Fleet;
	std::optional<Spline> m_Path;

public:
	
#pragma region custom vector overloads
	void erase(std::size_t index)				{			m_Fleet.erase(m_Fleet.begin() + index);	}
	auto& operator[](std::size_t index)			{			return m_Fleet[index];					}
	auto& operator[](std::size_t index) const	{			return m_Fleet[index];					}
	auto begin()								{			return m_Fleet.begin();					}
	auto end()									{			return m_Fleet.end();					}
	auto cbegin() const							{			return m_Fleet.begin();					}
	auto cend() const							{			return m_Fleet.end();					}
	auto begin() const							{			return m_Fleet.begin();					}
	auto end() const							{			return m_Fleet.end();					}
	size_t size() const							{			return m_Fleet.size();					}
#pragma endregion

	void update(const sf::Time& deltaTime);



	void setPath(const std::vector<sf::Vector2f>& waypoints);
	sf::FloatRect getRectangle() const;
	void move(const sf::Vector2f& moveBy);



	void addFleet(std::vector<EnemyShip::ptr> fleet)	{			m_Fleet = std::move(fleet);										}
	std::vector<EnemyShip::ptr>& getShips()				{			return m_Fleet;													}
	sf::Vector2f getSize()	const						{			return { getRectangle().width, getRectangle().height };			}

	using ptr = std::unique_ptr<Fleet>;
};