#pragma once
#include "Layout.h"
class VerticalLayout :
    public Layout
{
private:
    void updateShape() override;
public:
    VerticalLayout(opt_ref parent, float padding);
    virtual ~VerticalLayout();

    sf::Vector2f getSize() const override;

    void update(const sf::Time& deltaTime) override;

    using ptr = std::unique_ptr<VerticalLayout>;
};

