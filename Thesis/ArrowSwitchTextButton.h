#pragma once
#include "Label.h"
#include "ArrowSwitch.h"


class ArrowSwitchTextButton :
    public Button
{
private:
    float m_Padding;
    sf::RectangleShape m_Shape;
    Label m_Label;
    ArrowSwitch m_SwitchArea;

    sf::Color m_FillColor, m_HoverColor;

    void draw(sf::RenderTarget& target, sf::RenderStates) const override;

    virtual void processEvent(const sf::Event& sfevent) override;
    virtual void onMouseEntered() override;
    virtual void onMouseLeft() override;

    void initColors();

    void reposition();
    void repositionLabel();
    void repositionSwitchArea();
     
public:
    ArrowSwitchTextButton(opt_ref parent, const sf::Vector2f& size,
        std::string_view text, sf::Font& font, unsigned int charSize,
        unsigned int numberOfOptions, const sf::Vector2f& switchAreaSize,
        std::optional<sf::Vector2f> arrow_size = std::nullopt,
        const sf::Texture& left = Configuration::textures_options.get(Configuration::TexturesOptionsState::left_arrow),
        const sf::Texture& right = Configuration::textures_options.get(Configuration::TexturesOptionsState::right_arrow)
    );

    virtual ~ArrowSwitchTextButton();

    void addOption(std::string_view option, sf::Font& font, unsigned int charSize);
    std::string readValue()override;



#pragma region SETTERS / GETTERS

    /* BUTTON SETTERS */
    void setPosition(const sf::Vector2f& pos) override;
    void setOutlineThickness(float thickness);
    void setOutlineColor(const sf::Color& color);

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

    std::string getString()const;
#pragma endregion

};
