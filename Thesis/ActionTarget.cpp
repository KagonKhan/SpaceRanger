#include "ActionTarget.h"


template<typename T>
inline ActionTarget<T>::ActionTarget(const ActionMap<T>& map)
	: m_ActionMap(map)
{

}

template<typename T>
inline bool ActionTarget<T>::processEvent(const sf::Event& sfevent) const
{
	bool result = false;

	for(auto& pair: m_EventsPoll)
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

	if (action.m_Type == Action::Type::RealTime)
		m_EventsRealTime.emplace_back(key, callback);
	else
		m_EventsPoll.emplace_back(key, callback);
}

template<typename T>
inline void ActionTarget<T>::unbind(const T& key)
{
	auto remove_function = [key](const std::pair<T, FuncType>& pair) -> bool
	{
		return pair.first == key;
	};

	const Action& action = m_ActionMap.get(key);

	if (action.m_Type & Action::Type::RealTime)
		m_EventsRealTime.remove_if(remove_function);
	else
		m_EventsPoll.remove_if(remove_function);
}