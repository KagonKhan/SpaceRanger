#pragma once
#include "SFML/Graphics/Drawable.hpp"

class SpaceBackground
	: public sf::Drawable
{
private:
	void draw(sf::RenderTarget& target, sf::RenderStates) const override;
	
	sf::RenderWindow& m_Window;

	sf::IntRect m_TextRect;
	sf::Sprite m_Background;
	std::vector<sf::Sprite> m_BackgroundObjects;

	int m_MinDelay, m_MaxDelay;

	void spawnNebulis();
	void spawnPlanet();

	void cullObjects();

public:
	SpaceBackground(sf::RenderWindow& window, int minDelay, int maxDelay);
	~SpaceBackground();

	void update(const sf::Time& deltaTime);
};
