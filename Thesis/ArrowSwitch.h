#pragma once
#include "CircularArray.h"
#include "SpriteButton.h"

class ArrowSwitch : public Widget
{
    friend class ArrowSwitchTextButton;
private:
    float m_Padding;
    sf::RectangleShape m_AreaShape;
    CircularArray<Label> m_Options;
    SpriteButton m_Arrows[2];

    sf::Color m_FillColor, m_HoverColor;

    void draw(sf::RenderTarget& target, sf::RenderStates) const override;
    void drawBackground(sf::RenderTarget& target) const;
    void drawArrows(sf::RenderTarget& target) const;
    // Will crash if no options exist
    void drawCurrentOption(sf::RenderTarget& target) const;


    void processEvent(const sf::Event& sfevent) override;
    void processArrowButtonsEvent(const sf::Event& sfevent);

    void initColors();
    void initButtonFunctionalities();

    void reposition();
    void repositionButtons();
    void repositionOptions();

public:
    ArrowSwitch(opt_ref parent, unsigned int numberOfOptions, const sf::Vector2f& size, const sf::Texture& left, const sf::Texture& right, std::optional<sf::Vector2f> arrow_size);
    virtual ~ArrowSwitch();

    void addOption(std::string_view option, sf::Font& font, unsigned int charSize);

    void setPosition(const sf::Vector2f& pos);
    void setSize(const sf::Vector2f& size);
    sf::Vector2f getSize() const;


    std::string getString()const;
};