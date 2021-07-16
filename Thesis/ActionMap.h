#pragma once
#include "Action.h"

#include <unordered_map>

/* Wrapper for a map containing a key and an action associated with it */
template<typename T = int>
class ActionMap
{
private:
	/* Map of key and button */
	std::unordered_map<T, Action> m_Map;

public:
	ActionMap(const ActionMap<T>&) = delete;
	ActionMap<T>& operator= (const ActionMap<T>&) = delete;
	
	ActionMap() = default;

	/* Insert key and button/action */
	void map(const T& key, const Action& action);
	/* Get action assigned to a key*/
	const Action& get(const T& key) const;
};

template<typename T>
void ActionMap<T>::map(const T& key, const Action& action)
{
	m_Map.emplace(key, action);
}

template<typename T>
const Action& ActionMap<T>::get(const T& key) const
{
	return m_Map.at(key);
}