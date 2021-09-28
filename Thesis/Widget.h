#pragma once
#include "Configuration.h"

#pragma warning( disable : 4820)



class Widget :
	public sf::Drawable
{
public: using opt_ref = std::optional<std::reference_wrapper<Widget>>;

private:
	friend class Layout;
	friend class VerticalLayout;


protected:
	sf::Vector2f m_Position;
	opt_ref m_Parent;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates) const override = 0;
	virtual void processEvent(const sf::Event& sfevent);

public:
	Widget(opt_ref parent);
	virtual ~Widget();


	virtual void update(const sf::Time&);
	virtual void setPosition(const sf::Vector2f& pos) = 0;
	virtual void setPosition(float x, float y);

	virtual sf::Vector2f getSize() const = 0;
	const sf::Vector2f& getPosition() const;

	void setParent(opt_ref parent);

};

