#pragma once
#include "ActionMap.h"

#include <functional>
#include <utility>
#include <list>

/* Usage: Target should inherit from this, use the constructor, then bind functionality */
/* The constructor accepts ActionMap, which should be initialized earlier */
template <typename T = int>
class ActionTarget
{
private:
	using FuncType = std::function<void(const sf::Event&)>;

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

