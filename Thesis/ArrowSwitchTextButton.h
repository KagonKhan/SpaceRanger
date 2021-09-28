#pragma once
#include "Label.h"
#include "ArrowSwitch.h"


class ArrowSwitchTextButton :
    public Button
{
private:
    float                   m_Padding{ 10.f };
    sf::RectangleShape      m_Shape;
    Label                   m_Label;
    ArrowSwitch             m_SwitchArea;
    sf::Color               m_FillColor;
    sf::Color               m_HoverColor;

    void draw(sf::RenderTarget& target, sf::RenderStates) const override;

    virtual void processEvent(const sf::Event& sfevent) override;
    virtual void onMouseEntered() override { m_Shape.setFillColor(m_HoverColor); }
    virtual void onMouseLeft() override { m_Shape.setFillColor(m_FillColor); }

    void initColors();

    void reposition();
    void repositionLabel();
    void repositionSwitchArea();
     
public:
    ArrowSwitchTextButton(opt_ref parent, const sf::Vector2f& size,
        std::string_view text, const sf::Font& font, unsigned int charSize,
        unsigned int numberOfOptions, const sf::Vector2f& switchAreaSize,
        std::optional<sf::Vector2f> arrow_size = std::nullopt,
        const sf::Texture& left = Configuration::textures_options.get(Configuration::TexturesOptionsState::left_arrow),
        const sf::Texture& right = Configuration::textures_options.get(Configuration::TexturesOptionsState::right_arrow)
    );

    void addOption(std::string_view option, sf::Font& font, unsigned int charSize) { m_SwitchArea.addOption(option, font, charSize); }



#pragma region SETTERS / GETTERS

    /* BUTTON SETTERS */
    void setPosition(const sf::Vector2f& pos) override;
    void setSize(const sf::Vector2f& size);



    std::string readValue( ) override                    {        return m_SwitchArea.getString();            }
    void setOutlineThickness( float thickness )          {        m_Shape.setOutlineThickness(thickness);     }
    void setOutlineColor( const sf::Color& color )       {        m_Shape.setOutlineColor(color);             }
    sf::Vector2f getSize( ) const                        {        return m_Shape.getSize();                   }
    /* TEXT SETTERS */
    void setString( const std::string& string )          {        m_Label.setString(string);                  }
    void setFont( const sf::Font& font )                 {        m_Label.setFont(font);                      }
    void setCharacterSize( unsigned int size )           {        m_Label.setCharacterSize(size);             }
    void setLineSpacing( float spacingFactor )           {        m_Label.setLineSpacing(spacingFactor);      }
    void setLetterSpacing( float spacingFactor )         {        m_Label.setLetterSpacing(spacingFactor);    }
    void setTextStyle( sf::Uint32 style )                {        m_Label.setStyle(style);                    }
    void setTextFillColor( const sf::Color& color )      {        m_Label.setFillColor(color);                }
    void setTextOutlineColor( const sf::Color& color )   {        m_Label.setOutlineColor(color);             }
    void setTextOutlineThickness( float thickness )      {        m_Label.setOutlineThickness(thickness);     }
    unsigned int getCharacterSize( ) const               {        return m_Label.getCharacterSize();          }
    std::string getString( )const                        {        return m_Label.getString();                 }

#pragma endregion

};
