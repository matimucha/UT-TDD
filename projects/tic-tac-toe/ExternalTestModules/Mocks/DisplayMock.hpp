#pragma once

#include "Interfaces/Display.hpp"
#include <gmock/gmock.h>

class DisplayMock : public Display
{
public:
    MOCK_METHOD1(field, Field&(const Position&));
    MOCK_CONST_METHOD1(field, Field(const Position&));
    MOCK_CONST_METHOD0(update, void());
};

