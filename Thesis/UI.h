#pragma once

#include "Layout.h"
#include "ActionTarget.h"
#include "Button.h"

class UI : public Widget, protected ActionTarget<int>
{
private:
	sf::RenderWindow& window;
	std::vector<Layout*> _layouts;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override final;

	using ActionTarget<int>::FuncType;
public:
	UI(const UI&) = delete;
	UI& operator=(const UI&) = delete;

	UI(sf::RenderWindow& window, Widget* parent = nullptr);
	sf::Vector2f getSize() const override final;

	bool processEvent(const sf::Event& sfevent);

	void addLayout(Layout* layout);
	void setLayoutPosition(sf::Vector2f position);

	void bind(int key, const FuncType& callback);
	void unbind(int key);

};
