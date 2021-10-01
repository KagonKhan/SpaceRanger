#pragma once
#include "EnemyShip.h"

namespace Pos {
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
	std::optional<Spline> m_Path;

public:


	using PositionType = std::tuple< Pos::X, Pos::Place, Pos::Y, Pos::Place>;



#pragma region custom vector overloads
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
#pragma endregion

	Fleet(Fleet&& other) noexcept;
	Fleet& operator=(Fleet&& other) noexcept;
	explicit Fleet(std::vector<EnemyShip::ptr> fleet);
	explicit Fleet(EnemyShip::Type type, sf::FloatRect area, sf::Vector2f padding);

	~Fleet() override;


	
	
	void position(PositionType pos);


	void update(const sf::Time& deltaTime);

	void setPath(const std::vector<sf::Vector2f>& waypoints);
	sf::FloatRect getRectangle() const;
	void move(const sf::Vector2f& moveBy);
	void setWeaponsAsActive(bool active);


	void addShips(std::vector<EnemyShip::ptr> fleet)	{			m_Ships = std::move(fleet);										}
	std::vector<EnemyShip::ptr>& getShips()				{			return m_Ships;													}
	sf::Vector2f getSize()	const						{			return { getRectangle().width, getRectangle().height };			}

	using ptr = std::unique_ptr<Fleet>;
};