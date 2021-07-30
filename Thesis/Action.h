#pragma once
#pragma warning(disable : 26812)


/* Contains internal event, basis for ActionMap, wrapper for particular keys */
class Action
{
private:
	template<typename T> friend class ActionTarget;
	sf::Event m_Event;
	int m_Type;

public:

	enum Type {
		RealTime = 1,
		Pressed = 1 << 1,
		Released = 1 << 2
	};

	/* Add a keyboard key */
	Action(const sf::Keyboard::Key& key, int type = Type::RealTime | Type::Pressed);
	/* Add a mouse button */
	Action(const sf::Mouse::Button& key, int type = Type::RealTime | Type::Pressed);
	/* Copy action */
	Action(const Action& other);
	/* Assign action */
	Action& operator= (const Action& other);

	/* Test for real time events - Check if key/button is pressed */
	bool test() const;

	/* Comparison to other action */
	bool operator== (const Action& other) const;
	/* Comparison to event */
	bool operator== (const sf::Event& sfEvent) const;

};

