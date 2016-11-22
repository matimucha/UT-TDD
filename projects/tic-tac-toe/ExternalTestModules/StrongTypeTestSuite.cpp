#include "StrongType.hpp"
#include <gmock/gmock.h>

struct FooTag
{
    static void verify(int value)
    {
        if (value > 1000)
            throw std::runtime_error("verification failed");
    }
};

using Foo = StrongType<int, FooTag>;

using namespace testing;

TEST(StrongTypeTestSuite, staticCastsToSpecifiedType)
{
    auto sut = Foo(42);
    EXPECT_THAT(static_cast<int>(sut), Eq(42));
}

TEST(StrongTypeTestSuite, equalsToOtherStrongType)
{
    EXPECT_THAT(Foo(42), Eq(Foo(42)));
    EXPECT_THAT(Foo(42), Not(Eq(Foo(30))));
}

TEST(StrongTypeTestSuite, canBeCopiedFromOtherStrongType)
{
    EXPECT_THAT(Foo(Foo(42)), Eq(Foo(42)));
}

TEST(StrongTypeTestSuite, lessToOtherStrongTypes)
{
    EXPECT_THAT(Foo(30), Lt(Foo(42)));
    EXPECT_THAT(Foo(30), Not(Lt(Foo(30))));
    EXPECT_THAT(Foo(42), Not(Lt(Foo(30))));
}

TEST(StrongTypeTestSuite, verifiesIsPerformedDuringCreation)
{
    EXPECT_THROW(Foo(1024), std::runtime_error);
}
