#include "Interfaces/Position.hpp"
#include <gmock/gmock.h>

using namespace testing;

TEST(PositionTestSuite, throwsExceptionWhenValueIsOutOfRange)
{
    EXPECT_THROW(Position(0), std::runtime_error);
    EXPECT_THROW(Position(10), std::runtime_error);
}
