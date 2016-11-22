#pragma once

#include "StrongType.hpp"

#include <cstdint>

struct PositionTag
{
    static void verify(size_t value)
    {
        if (value < 1u or value > 9u)
            throw std::runtime_error("invalid position");
    }
};

using Position = StrongType<size_t, PositionTag>;

