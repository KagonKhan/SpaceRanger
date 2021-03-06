#pragma once
#include "ActionTarget.h"

class UserInterface : 
    public Widget,
    protected ActionTarget<int>
{
private:
	void draw(sf::RenderTarget& target, sf::RenderStates) const override;

	std::vector<std::unique_ptr<Layout>> m_Layouts;

	void reposition();

	using ActionTarget<int>::FuncType;
public:
    UserInterface();


    void addLayout(std::unique_ptr<Layout> layout);
	void bind(int key, const FuncType& callback);
	void unbind(int key);
    
    __declspec(deprecated("** use 'setPositionAtIndex version **")) void setPosition(const sf::Vector2f&) override {};
    __declspec(deprecated("** use 'setPositionAtIndex version **")) void setPosition(float, float) override {};

    sf::Vector2f getSize() const final;
    void setPositionAtIndex(const sf::Vector2f& pos, unsigned int index);
    void setPositionAtIndex(float x, float y, unsigned int index);
    const std::vector<Widget*> getAllWidgets() const;
    const Layout* getLayoutAtIndex(unsigned int index) const;


    void processEvent(const sf::Event& sfevent) final;

    void update(const sf::Time& deltaTime) final;

};
