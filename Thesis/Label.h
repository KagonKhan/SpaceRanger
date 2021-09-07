#pragma once
#include "Widget.h"

class Label :
    public Widget
{
private:
    void draw(sf::RenderTarget& target, sf::RenderStates) const override;

    sf::Text m_Text;

public:
    Label();
    Label(opt_ref parent, std::string_view text, const sf::Font& font = Configuration::fonts.get(Configuration::Fonts::SpaceGui), unsigned int characterSize = 25U);
    virtual ~Label();

#pragma region SETTERS / GETTERS
    enum Style
    {
        Regular = 0,      ///< Regular characters, no style
        Bold = 1 << 0, ///< Bold characters
        Italic = 1 << 1, ///< Italic characters
        Underlined = 1 << 2, ///< Underlined characters
        StrikeThrough = 1 << 3  ///< Strike through characters
    };

    void setPosition(const sf::Vector2f& pos) override;
    using Widget::setPosition;
    virtual sf::Vector2f getSize() const;


    void setString(const sf::String& string);
    void setFont(const sf::Font& font);
    void setCharacterSize(unsigned int size);

    void setLineSpacing(float spacingFactor);
    void setLetterSpacing(float spacingFactor);
    void setStyle(sf::Uint32 style);
    void setFillColor(const sf::Color& color);
    void setOutlineColor(const sf::Color& color);
    void setOutlineThickness(float thickness);
    unsigned int getCharacterSize() const;

    sf::Color getOutlineColor() const;
    std::string getString()const;
#pragma endregion


};

