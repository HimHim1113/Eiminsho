#pragma once

#include <list>
#include <memory>
#include <array>
#include "Surface.h"
#include "AbstractBack.h"

class Back01 final : public AbstractBack
{

public:
    Back01();
    ~Back01() = default;
    bool update() override;
    void draw() const override;

private:
    void draw(VECTOR offset) const;

    std::list<std::shared_ptr<Surface>> _list;
    std::array<int, Surface::DATANUM> _handle;

};
