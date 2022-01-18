#pragma once
#include "ActionMap.h"



/* Usage: Target should inherit from this, use the constructor, then bind functionality */
/* The constructor accepts ActionMap, which should be initialized earlier */
template <typename T = int>
class ActionTarget
{
public:
	using FuncType = std::function<void(const sf::Event&)>;

private:
	/* Events for real time checking */
	std::list<std::pair<T, FuncType>> m_EventsRealTime;
	/* Events that are polled */
	std::list<std::pair<T, FuncType>> m_EventsPoll;
	/* Reference to the Action Map */
	const ActionMap<T>& m_ActionMap;

public:

	ActionTarget(const ActionTarget<T>&) = delete;
	ActionTarget<T>& operator=(const ActionTarget<T>&) = delete;

	ActionTarget(const ActionMap<T>& map);

	bool processEvent(const sf::Event& sfevent) const;
	void processEvents() const;

	/* Add functionality to a key */
	void bind(const T& key, const FuncType& callback);
	/* Remove functionality from a key */
	void unbind(const T& key);
};


/* ========================================================== IMPLEMENTATION ========================================================== */
template<typename T>
inline ActionTarget<T>::ActionTarget(const ActionMap<T>& map)
	: m_ActionMap(map)
{
}

template<typename T>
inline bool ActionTarget<T>::processEvent(const sf::Event& sfevent) const
{
	bool result = false;

	for (auto& pair : m_EventsPoll)
		if (m_ActionMap.get(pair.first) == sfevent) {
			pair.second(sfevent);
			result = true;
			break;
		}
	return result;
}

template<typename T>
inline void ActionTarget<T>::processEvents() const
{
	for (auto& pair : m_EventsRealTime) {
		const Action& action = m_ActionMap.get(pair.first);

		if (action.test())
			pair.second(action.m_Event);
	}
}

template<typename T>
inline void ActionTarget<T>::bind(const T& key, const FuncType& callback)
{
	const Action& action = m_ActionMap.get(key);

	if (action.m_Type & Action::Type::RealTime)
		m_EventsRealTime.emplace_back(key, callback);
	else
		m_EventsPoll.emplace_back(key, callback);
}

template<typename T>
inline void ActionTarget<T>::unbind(const T& key)
{
	auto remove_function = [&key](const std::pair<T, FuncType>& pair) -> bool
	{
		return pair.first == key;
	};

	const Action& action = m_ActionMap.get(key);

	if (action.m_Type & Action::Type::RealTime)
		m_EventsRealTime.remove_if(remove_function);
	else
		m_EventsPoll.remove_if(remove_function);
}