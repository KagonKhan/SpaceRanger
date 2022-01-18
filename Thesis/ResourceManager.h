#pragma once
#include "Collision.h"

template <typename RESOURCE, typename IDENTIFIER = int>
class ResourceManager
{
private:
	std::map<IDENTIFIER, std::unique_ptr<RESOURCE>> m_ResMap; 

public:
	ResourceManager(const ResourceManager&) = delete;
	ResourceManager& operator=(const ResourceManager&) = delete;
	ResourceManager() = default;

	template<typename ... Args>
	RESOURCE& load(const IDENTIFIER& id, Args&& ... args);
	RESOURCE& get(const IDENTIFIER& id) const;
};

template<typename RESOURCE, typename IDENTIFIER>
template<typename ... Args>
RESOURCE& ResourceManager<RESOURCE, IDENTIFIER>::load(const IDENTIFIER& id, Args&& ... args)
{
	auto ptr = std::make_unique<RESOURCE>();
	if (!ptr->loadFromFile(std::forward<Args>(args)...))
		throw std::runtime_error("[EROR] Cannot load file\n");

	m_ResMap.emplace(id, std::move(ptr));

	return *m_ResMap.rbegin()->second;
}

template<typename RESOURCE, typename IDENTIFIER>
RESOURCE& ResourceManager<RESOURCE, IDENTIFIER>::get(const IDENTIFIER& id) const
{
	return *m_ResMap.at(id);
}


/* ==================================== Textures ==================================*/
template <typename IDENTIFIER>
class ResourceManager<sf::Texture, IDENTIFIER>
{
private:
	std::map<IDENTIFIER, std::unique_ptr<sf::Texture>> m_ResMap;

public:
	ResourceManager(const ResourceManager&) = delete;
	ResourceManager& operator=(const ResourceManager&) = delete;
	ResourceManager() = default;

	template<typename ... Args>
	sf::Texture& load(const IDENTIFIER& id, Args&& ... args);
	sf::Texture& loadAndBitmask(const IDENTIFIER& id, std::string path);
	sf::Texture& get(const IDENTIFIER& id) const;
};

template<typename IDENTIFIER>
template<typename ... Args>
sf::Texture& ResourceManager<sf::Texture, IDENTIFIER>::load(const IDENTIFIER& id, Args&& ... args)
{
	auto ptr = std::make_unique<sf::Texture>();
	if (!ptr->loadFromFile(std::forward<Args>(args)...))
		throw std::runtime_error("[EROR] Cannot load file\n");

	m_ResMap.emplace(id, std::move(ptr));

	return *m_ResMap.rbegin()->second;
}
template<typename IDENTIFIER>
sf::Texture& ResourceManager<sf::Texture, IDENTIFIER>::loadAndBitmask(const IDENTIFIER& id, std::string path)
{
	auto ptr = std::make_unique<sf::Texture>();
	if (!Collision::CreateTextureAndBitmask(*ptr, path))
		throw std::runtime_error("[EROR] Cannot load file\n");

	m_ResMap.emplace(id, std::move(ptr));

	return *m_ResMap.rbegin()->second;
}

template<typename IDENTIFIER>
sf::Texture& ResourceManager<sf::Texture, IDENTIFIER>::get(const IDENTIFIER& id) const
{
	return *m_ResMap.at(id);
}


/* ==================================== MUSIC ==================================*/
template <typename IDENTIFIER>
class ResourceManager<sf::Music, IDENTIFIER>
{
private:
	std::map<IDENTIFIER, std::unique_ptr<sf::Music>> m_ResMap;

public:
	ResourceManager(const ResourceManager&) = delete;
	ResourceManager& operator=(const ResourceManager&) = delete;
	ResourceManager() = default;

	template<typename ... Args>
	sf::Music& load(const IDENTIFIER & id, Args&& ... args);
	sf::Music& get(const IDENTIFIER & id) const;

};

template<typename IDENTIFIER>
template<typename ... Args>
sf::Music& ResourceManager<sf::Music, IDENTIFIER>::load(const IDENTIFIER& id, Args&& ... args)
{
	auto ptr = std::make_unique<sf::Music>();
	if (!ptr->openFromFile(std::forward<Args>(args)...))
		throw std::runtime_error("[EROR] Cannot load file\n");

	m_ResMap.emplace(id, std::move(ptr));

	return *m_ResMap.rbegin()->second;
}

template<typename IDENTIFIER>
sf::Music& ResourceManager<sf::Music, IDENTIFIER>::get(const IDENTIFIER& id) const
{
	return *m_ResMap.at(id);
}