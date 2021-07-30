#pragma once
#pragma warning(disable : 4244)

class Collision
{
public:
	Collision() = delete;
	Collision(const Collision&) = delete;
	Collision& operator= (const Collision&) = delete;

	static bool CircleTest(const sf::Sprite& first, const sf::Sprite& second);
};

