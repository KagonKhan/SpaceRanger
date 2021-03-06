#pragma once
#include "Layout.h"
class UnorderedLayout :
    public Layout
{
private:
    void updateShape() override;
public:
    UnorderedLayout(opt_ref parent);
    virtual ~UnorderedLayout();

    sf::Vector2f getSize() const override;

    void update(const sf::Time& deltaTime) override;


    using ptr = std::unique_ptr<UnorderedLayout>;
};


