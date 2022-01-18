#pragma once
#include "Configuration.h"

#pragma warning( disable : 4820) // Ignore padding and alignment warnings

class Widget :
	public sf::Drawable
{
public: using opt_ref = std::optional<std::reference_wrapper<Widget>>;

private:
	friend class Layout;
	friend class VerticalLayout;
	friend class TableLayout;
	friend class UnorderedLayout;


protected:
	sf::Vector2f m_Position;
	opt_ref m_Parent;

	virtual void processEvent(const sf::Event& sfevent) {};

public:
	Widget(opt_ref parent);


	virtual void update(const sf::Time&) {};

	virtual sf::Vector2f getSize() const				= 0;
	virtual void setPosition(const sf::Vector2f& pos)	= 0;
	virtual void setPosition(float x, float y)	{		setPosition(sf::Vector2f(x, y));	};
	const sf::Vector2f& getPosition() const		{		return m_Position;		};
	void setParent(opt_ref parent)				{		m_Parent = parent;		};

};

