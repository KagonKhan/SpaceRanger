#pragma once
#include "Button.h"
#include "Label.h"

// For now the class throws exceptions when Label does not exist, accessing it's functions
class SpriteButton :
    public Button
{
friend class ArrowSwitch;
private:
    void draw(sf::RenderTarget& target, sf::RenderStates) const override;

    sf::Sprite m_Sprite;
    std::optional<Label> m_Label{ std::nullopt };

    virtual void processEvent(const sf::Event& sfevent);
    virtual void onMouseEntered()                           {       m_Sprite.setColor(sf::Color(182, 182, 182));        }
    virtual void onMouseLeft()                              {       m_Sprite.setColor(sf::Color::White);                }

    void positionTextBasedOnStyle();

public:
    // No label
    SpriteButton(opt_ref parent, std::optional<sf::Vector2f> size, const sf::Texture& texture);
    // Creates label
    SpriteButton(opt_ref parent, std::optional<sf::Vector2f> size, const sf::Texture& texture,
        std::string_view text, sf::Font& font, unsigned int charSize = 25);


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
    } m_Style{ Style::Middle };

#pragma region SETTERS / GETTERS

    /* BUTTON SETTERS */
    void setPosition(const sf::Vector2f& pos) override;
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
    void setTextFillColor(const sf::Color& color)           {       m_Label.value().setFillColor(color);                }
    void setTextOutlineColor(const sf::Color& color)        {       m_Label.value().setOutlineColor(color);             }
    void setTextOutlineThickness(float thickness)           {       m_Label.value().setOutlineThickness(thickness);     }
    unsigned int getCharacterSize() const                   {       return m_Label.value().getCharacterSize();          }

#pragma endregion

};
