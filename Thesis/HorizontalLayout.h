#pragma once
#include "Layout.h"
class HorizontalLayout :
    public Layout
{
private:
    void updateShape() override;
public:
    HorizontalLayout(opt_ref parent, float padding);
    virtual ~HorizontalLayout();

    sf::Vector2f getSize() const override;

    void update(const sf::Time& deltaTime) override;


    using ptr = std::unique_ptr<HorizontalLayout>;
};

