#pragma once
#include "EnemyShip.h"

namespace pos {
	enum class X { Left, Middle, Right, };
	enum class Y { Top, Middle, Bottom, };
	enum class Place { Inside, Outside, };
}



class Fleet : 
	public sf::Drawable
{
private:
	void draw(sf::RenderTarget& target, sf::RenderStates) const override;
	std::vector<EnemyShip::ptr> m_Ships;

	std::pair<std::queue<MoveCommand>, bool> m_MoveQueue;


public:

#pragma region vector overloads
	void erase(std::size_t index)				{			m_Ships.erase(m_Ships.begin() + index);	}
	auto& operator[](std::size_t index)			{			return m_Ships[index];					}
	auto& operator[](std::size_t index) const	{			return m_Ships[index];					}
	auto begin()								{			return m_Ships.begin();					}
	auto end()									{			return m_Ships.end();					}
	auto cbegin() const							{			return m_Ships.begin();					}
	auto cend() const							{			return m_Ships.end();					}
	auto begin() const							{			return m_Ships.begin();					}
	auto end() const							{			return m_Ships.end();					}
	size_t size() const							{			return m_Ships.size();					}
	Fleet(Fleet&& other) noexcept;
	Fleet& operator=(Fleet&& other) noexcept;
#pragma endregion

	explicit Fleet(std::vector<EnemyShip::ptr> fleet);
	Fleet() = default;
	~Fleet()override = default;
	Fleet(EnemyShip::Type type, sf::FloatRect area, sf::Vector2f padding, bool randomize);

	using ptr = std::unique_ptr<Fleet>;
	using PositionType = std::tuple< pos::X, pos::Place, pos::Y, pos::Place>;
	
	void update(const sf::Time& deltaTime);
	
	void setPosition(PositionType pos) const;


	void addMovementToQueue(sf::Vector2f dir, float length);

	void setPath(const std::vector<sf::Vector2f>& waypoints) const;
	void setPath(Spline path) const;
	sf::FloatRect getRectangle() const;
	void move(const sf::Vector2f& moveBy) const;
	void setWeaponsAsActive(bool active) const;


	void addShips(std::vector<EnemyShip::ptr> fleet)	{			m_Ships = std::move(fleet);										}
	std::vector<EnemyShip::ptr>& getShips()				{			return m_Ships;													}
	sf::Vector2f getSize()	const						{			return { getRectangle().width, getRectangle().height };			}

};