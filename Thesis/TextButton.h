#pragma once
#include "Button.h"
#include "Label.h"

class TextButton :
    public Button
{
protected:
    void draw(sf::RenderTarget& target, sf::RenderStates) const override;

    sf::RectangleShape m_Shape;
    sf::Color m_OutlineColor, m_FillColor;
    bool m_IsAutoAdjustable;

    Label m_Label;


    virtual void processEvent(const sf::Event& sfevent) override;
    virtual void onMouseEntered() override;
    virtual void onMouseLeft() override;

    virtual void positionTextBasedOnStyle();
    virtual void adjustSizeToLabel();

public:
    TextButton(opt_ref parent, std::optional<sf::Vector2f> size, const sf::Color& fillColor,
        std::string_view text, sf::Font& font = Configuration::fonts.get(Configuration::Fonts::SpaceGui), unsigned int charSize = 25);
    virtual ~TextButton();

    // Text positioning
    enum class Style
    {
        TopLeft = 1 << 0,
        TopMiddle = 1 << 1,
        TopRight = 1 << 2,
        MiddleLeft = 1 << 3,
        Middle = 1 << 4,
        MiddleRight = 1 << 5,
        BottomLeft = 1 << 6,
        BottomMiddle = 1 << 7,
        BottomRight = 1 << 8
    } m_Style;

    void setIsAutoAdjustable(bool adjust);

#pragma region SETTERS / GETTERS

    /* BUTTON SETTERS */
    void setPosition(const sf::Vector2f& pos) override;
    void setFillColor(const sf::Color& color);
    void setOutlineThickness(float thickness);
    void setOutlineColor(const sf::Color& color);
    void setStyle(Style style);

    void setSize(const sf::Vector2f& size);
    sf::Vector2f getSize() const;


    /* TEXT SETTERS */
    void setString(const std::string& string);
    void setFont(const sf::Font& font);
    void setCharacterSize(unsigned int size);
    void setLineSpacing(float spacingFactor);
    void setLetterSpacing(float spacingFactor);
    void setTextStyle(sf::Uint32 style);
    void setTextFillColor(const sf::Color& color);
    void setTextOutlineColor(const sf::Color& color);
    void setTextOutlineThickness(float thickness);
    unsigned int getCharacterSize() const;

#pragma endregion

};