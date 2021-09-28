#pragma once
#include "SFML/Graphics/Drawable.hpp"




class SpaceBackground :
	public sf::Drawable,
	public sf::NonCopyable

{
private:
	void draw(sf::RenderTarget& target, sf::RenderStates) const override;
	
	sf::RenderWindow&									m_Window;
	sf::Vector2f										m_WinSize;
	int													m_MinDelay;
	int													m_MaxDelay;
	sf::IntRect											m_TextRect;
	sf::Sprite											m_Background;
	std::vector<std::pair<sf::Sprite,sf::Vector2f>>		m_BackgroundObjects;


	void spawnNebulis();
	void spawnPlanet();

	void cullObjects();

public:
	SpaceBackground(sf::RenderWindow& window, int minDelay, int maxDelay);

	void update(const sf::Time& deltaTime);
};
