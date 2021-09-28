#include "pch.h"
#include "SpaceBackground.h"

void SpaceBackground::draw(sf::RenderTarget& target, sf::RenderStates) const
{
	target.draw(m_Background);
	for (auto&& [sprite, velocity] : m_BackgroundObjects)
		target.draw(sprite);

}

SpaceBackground::SpaceBackground(sf::RenderWindow& window, int minDelay, int maxDelay)
	: m_Window(window), m_WinSize(m_Window.getSize()),m_MinDelay(minDelay), m_MaxDelay(maxDelay),
	  m_TextRect(-2 * static_cast<int>(m_Window.getSize().x), 0, 4 * static_cast<int>(m_Window.getSize().x), 1000 * static_cast<int>(m_Window.getSize().y)),
	  m_Background(Configuration::textures_space.get(Configuration::TexturesSpaceState::background), m_TextRect)
{
	/* TODO: cleanup*/
	m_Background.setPosition(-2.f * static_cast<float>(m_Window.getSize().x), -995.f * static_cast<float>(m_Window.getSize().y));
}

void SpaceBackground::update(const sf::Time& deltaTime)
{
	m_Background.move(0, 20 * deltaTime.asSeconds());

	static auto spawnTime = static_cast<float>(Helpers::getRandom(m_MinDelay,m_MaxDelay));
	static auto currTime  = 0.f;

	currTime += deltaTime.asSeconds();
	
	if (currTime > spawnTime) {
		cullObjects();

		if (Helpers::getRandom(0, 100) == 56)
			spawnPlanet();
		else if (Helpers::getRandom(0, 50) >= 45)
			spawnNebulis();

		spawnTime = static_cast<float>(Helpers::getRandom(m_MinDelay, m_MaxDelay));
		currTime = 0.f;
	}

	for (auto&&[sprite, velocity]: m_BackgroundObjects)
		sprite.move(velocity * deltaTime.asSeconds());
}


void SpaceBackground::spawnNebulis()
{
	int id = Helpers::getRandom(1, 3);
	m_BackgroundObjects.emplace_back(Configuration::textures_space.get(Configuration::TexturesSpaceState(id)), sf::Vector2f(0.f, Helpers::getRandom(50.f, 80.f)));
	sf::Sprite& sprite = m_BackgroundObjects.back().first;

	sprite.setOrigin(sprite.getGlobalBounds().width / 2.f, sprite.getGlobalBounds().height / 2.f);

	sprite.setScale(0.2f, 0.2f);

	if (id <= 3)
		sprite.setScale(Helpers::getRandom(2.f, 5.f), Helpers::getRandom(2.f, 6.f));

	if (id == 1)
		sprite.setColor(sf::Color(100, 0, 200, 255));
	else
		sprite.setColor(sf::Color(60, 60, 60, 255));

	sprite.setPosition(Helpers::getRandom(0.f, m_WinSize.x), -2000.f);

}

void SpaceBackground::spawnPlanet()
{
	int id = Helpers::getRandom(4, 8);

	// Wouldn't the compiler already auto move it?
	m_BackgroundObjects.emplace_back(Configuration::textures_space.get(Configuration::TexturesSpaceState(id)), sf::Vector2f(0.f, Helpers::getRandom(5.f, 20.f)));
	sf::Sprite& sprite = m_BackgroundObjects.back().first;

	sprite.setOrigin(sprite.getGlobalBounds().width / 2.f, sprite.getGlobalBounds().height / 2.f);

	sprite.setScale(0.2f, 0.2f);

	sprite.setColor(sf::Color(25, 25, 25, 255));

	sprite.setPosition(Helpers::getRandom(0.f, m_WinSize.x), -2000.f);
}

void SpaceBackground::cullObjects()
{
	auto size = static_cast<float>(m_Window.getSize().y);

	for (int i = 0; i < static_cast<int>(m_BackgroundObjects.size()); ++i) 
		if (m_BackgroundObjects[i].first.getGlobalBounds().top > size)
			m_BackgroundObjects.erase(std::begin(m_BackgroundObjects) + i);
}
