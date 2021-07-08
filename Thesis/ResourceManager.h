#pragma once
#include <unordered_map>
#include <memory>
#include <string>
#include "SFML/Audio.hpp"

#include <stdexcept>
#include <utility>


template <typename RESOURCE, typename IDENTIFIER = int>
class ResourceManager
{
private:
	std::unordered_map<IDENTIFIER, std::unique_ptr<RESOURCE>> m_ResMap;

public:
	ResourceManager(const ResourceManager&) = delete;
	ResourceManager& operator=(const ResourceManager&) = delete;
	ResourceManager() = default;

	template<typename ... Args>
	void load(const IDENTIFIER& id, Args&& ... args);
	RESOURCE& get(const IDENTIFIER& id) const;
};

template<typename RESOURCE, typename IDENTIFIER>
template<typename ... Args>
void ResourceManager<RESOURCE, IDENTIFIER>::load(const IDENTIFIER& id, Args&& ... args)
{
	std::unique_ptr<RESOURCE> ptr(new RESOURCE);
	if (!ptr->loadFromFile(std::forward<Args>(args)...))
		throw std::runtime_error("[EROR] Cannot load file\n");

	m_ResMap.emplace(id, std::move(ptr));
}

template<typename RESOURCE, typename IDENTIFIER>
RESOURCE& ResourceManager<RESOURCE, IDENTIFIER>::get(const IDENTIFIER& id) const
{
	return *m_ResMap.at(id);
}



/* ==================================== MUSIC ==================================*/
template <typename IDENTIFIER>
class ResourceManager<sf::Music, IDENTIFIER>
{
private:
	std::unordered_map<IDENTIFIER, std::unique_ptr<RESOURCE>> m_ResMap;

public:
	ResourceManager(const ResourceManager&) = delete;
	ResourceManager& operator=(const ResourceManager&) = delete;
	ResourceManager() = default;

	template<typename ... Args>
	void load(const IDENTIFIER & id, Args&& ... args);
	sf::Music& get(const IDENTIFIER & id) const;

};

template<typename IDENTIFIER>
template<typename ... Args>
void ResourceManager<sf::Music, IDENTIFIER>::load(const IDENTIFIER& id, Args&& ... args)
{
	std::unique_ptr<sf::Music> ptr(new sf::Music);
	if (!ptr->openFromFile(std::forward<Args>(args)...))
		throw std::runtime_error("[EROR] Cannot load file\n");

	m_ResMap.emplace(id, std::move(ptr));
}

template<typename IDENTIFIER>
sf::Music& ResourceManager<sf::Music, IDENTIFIER>::get(const IDENTIFIER& id) const
{
	return *m_ResMap.at(id);
}