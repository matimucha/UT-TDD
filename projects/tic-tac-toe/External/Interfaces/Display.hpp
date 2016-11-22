#pragma once

#include "Interfaces/Position.hpp"
#include "Interfaces/Field.hpp"

class Display
{
public:
    virtual ~Display() = default;

    virtual Field& field(const Position&) = 0;
    virtual Field field(const Position&) const = 0;
    virtual void update() const = 0;
};

