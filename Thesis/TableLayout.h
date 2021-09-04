#pragma once
#include "Layout.h"
class TableLayout :
    public Layout
{
private:
    const sf::FloatRect m_Boundaries;

    void updateShape() override;

public:
    TableLayout(opt_ref parent, float padding, const sf::FloatRect& boundaries);
    virtual ~TableLayout();

    sf::Vector2f getSize() const override;

    void update(const sf::Time& deltaTime) override;
};

