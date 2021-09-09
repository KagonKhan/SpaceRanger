#include "pch.h"
#include "SpaceBackground.h"

void SpaceBackground::draw(sf::RenderTarget& target, sf::RenderStates) const
{
	target.draw(m_Background);
	for (auto&& obj : m_BackgroundObjects)
		target.draw(obj);

}

SpaceBackground::SpaceBackground(sf::RenderWindow& window, int minDelay, int maxDelay)
	: m_Window(window), m_MinDelay(minDelay), m_MaxDelay(maxDelay),
	  m_TextRect(0, 0, 2 * static_cast<int>(m_Window.getSize().x), 1000 * static_cast<int>(m_Window.getSize().y)),
	  m_Background(Configuration::textures_space.get(Configuration::TexturesSpaceState::background), m_TextRect)
{
	m_Background.setPosition(0, -999 * static_cast<int>(m_Window.getSize().y));
}

SpaceBackground::~SpaceBackground()
{
}

void SpaceBackground::update(const sf::Time& deltaTime)
{
	srand(time(NULL));
	m_Background.move(0, 20 * deltaTime.asSeconds());

	static int spawnTime = m_MinDelay + rand() % (m_MaxDelay - m_MinDelay);
	static float currTime = 0;

	currTime += deltaTime.asSeconds();
	
	if (currTime > spawnTime) {
		cullObjects();

		if (rand() % 100 == 56)
			spawnPlanet();
		else if (rand() %50 >= 45)
			spawnNebulis();//spawnNebulis();

		currTime = 0;
		spawnTime = m_MinDelay + rand() % (m_MaxDelay-m_MinDelay);
	}

	for (auto&& bg : m_BackgroundObjects)
		bg.move(0, 50 * deltaTime.asSeconds());
}


void SpaceBackground::spawnNebulis()
{
	int id = 1 + rand() % 3;
	m_BackgroundObjects.emplace_back(Configuration::textures_space.get(Configuration::TexturesSpaceState(id)));
	sf::Sprite& sprite = m_BackgroundObjects.back();

	sprite.setOrigin(sprite.getGlobalBounds().width / 2.f, sprite.getGlobalBounds().height / 2.f);

	sprite.setScale(0.2f, 0.2f);

	if (id <= 3)
		sprite.setScale(2 + rand() % 4, 2 + rand() % 4);

	if (id == 1)
		sprite.setColor(sf::Color(100, 0, 200, 255));
	else
		sprite.setColor(sf::Color(60, 60, 60, 255));

	sprite.setPosition(rand() % m_Window.getSize().x, -1000.f);

}

void SpaceBackground::spawnPlanet()
{
	int id = 4 + rand() % 5;

	m_BackgroundObjects.emplace_back(Configuration::textures_space.get(Configuration::TexturesSpaceState(id)));
	sf::Sprite& sprite = m_BackgroundObjects.back();

	sprite.setOrigin(sprite.getGlobalBounds().width / 2.f, sprite.getGlobalBounds().height / 2.f);

	sprite.setScale(0.2f, 0.2f);

	sprite.setColor(sf::Color(25, 25, 25, 255));

	sprite.setPosition(rand() % m_Window.getSize().x, -1000.f);
}

void SpaceBackground::cullObjects()
{
	static float size = static_cast<float>(m_Window.getSize().y);

	for (int i = 0; i < m_BackgroundObjects.size(); ++i) 
		if (m_BackgroundObjects[i].getGlobalBounds().top > size)
			m_BackgroundObjects.erase(std::begin(m_BackgroundObjects) + i);
}
