#pragma once
#include "Widget.h"
#include "Label.h"
class ScrollBarButton :
    public Widget
{
private:
    sf::RectangleShape m_BackgroundRectangle;
    sf::RectangleShape m_ScrollingButton;
    
    Label m_Label;

    sf::Vector2f m_MousePos;

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    virtual void processEvent(const sf::Event& sfevent) override;

    void updateMousePosition();

public:
    ScrollBarButton(const ScrollBarButton&) = delete;
    ScrollBarButton operator=(const ScrollBarButton&) = delete;

    ScrollBarButton(const sf::Vector2f& size, std::string_view text, Widget* parent = nullptr);
    ~ScrollBarButton();

    float getValue() const;

    void setPosition(const sf::Vector2f& pos) override;
    void setPosition(float x, float y) override;
    sf::Vector2f getSize() const override;

    void update(const sf::Time& deltaTime);

};

