#pragma once
#include "ActionTarget.h"



class UserInterface : public Widget, protected ActionTarget<int>
{
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates) const override;

	std::vector<std::unique_ptr<Layout>> m_Layouts;
	void recalculatePositionVariable();

	using ActionTarget<int>::FuncType;
public:
    UserInterface();
    virtual ~UserInterface();

    __declspec(deprecated("** use 'setPositionAtIndex version **")) void setPosition(const sf::Vector2f&) override {};
    __declspec(deprecated("** use 'setPositionAtIndex version **")) void setPosition(float, float) override {};

    void setPositionAtIndex(const sf::Vector2f& pos, unsigned int index);
    void setPositionAtIndex(float x, float y, unsigned int index);

    void processEvent(const sf::Event& sfevent);

    sf::Vector2f getSize() const;

    /* std::move into this*/
    void addLayout(std::unique_ptr<Layout> layout);

    void update(const sf::Time& deltaTime);

	void bind(int key, const FuncType& callback);
	void unbind(int key);


    const std::vector<Widget*> getAllWidgets() const;

};
