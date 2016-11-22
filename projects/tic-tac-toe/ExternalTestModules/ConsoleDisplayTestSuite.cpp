#include "ConsoleDisplay.hpp"
#include <sstream>
#include <regex>
#include <gmock/gmock.h>

using namespace testing;
using namespace std::literals;

auto matches(const std::array<std::string, 3>& rows)
{
    return MatchesRegex(".*"s + rows[0] + ".*\n.*"s + rows[1] + ".*\n.*"s + rows[2] + ".*\n"s);
}

size_t count(const std::stringstream& stream, char expected)
{
    auto text = stream.str();
    return std::count(std::begin(text), std::end(text), expected);
}

struct ConsoleDisplayTestSuite : public Test
{
    std::stringstream stream;

    ConsoleDisplay sut{ stream };
};

TEST_F(ConsoleDisplayTestSuite, containsOnlyBlanksAfterCreated)
{
    sut.update();

    EXPECT_THAT(count(stream, ' '), Eq(9ul));
}

struct ConsoleDisplayTestSuite_with2OsAnd1X : public ConsoleDisplayTestSuite
{
    void SetUp() override
    {
        sut.field(Position(5)) = ::Field::O;
        sut.field(Position(7)) = ::Field::X;
        sut.field(Position(9)) = ::Field::O;
    }
};

TEST_F(ConsoleDisplayTestSuite_with2OsAnd1X, displaysBlankCharacters)
{
    sut.update();

    EXPECT_THAT(count(stream, ' '), Eq(6ul));
}

TEST_F(ConsoleDisplayTestSuite_with2OsAnd1X, displaysOCharacters)
{
    sut.update();

    EXPECT_THAT(count(stream, 'O'), Eq(2ul));
}

TEST_F(ConsoleDisplayTestSuite_with2OsAnd1X, displaysXCharacters)
{
    sut.update();

    EXPECT_THAT(count(stream, 'X'), Eq(1ul));
}

using CheckRowsParams = std::tuple<
    std::map<Position, ::Field>,
    std::array<std::string, 3>
>;

struct ConsoleDisplayTestSuite_CheckRows : public ConsoleDisplayTestSuite,
                                           public WithParamInterface<CheckRowsParams>
{
    void SetUp() override
    {
        initialFields = fromParam<decltype(initialFields)>();
        expectedRowPatern = fromParam<decltype(expectedRowPatern)>();
    }

    template <class T>
    T fromParam()
    {
        return std::get<T>(GetParam());
    }

    std::map<Position, ::Field> initialFields{};
    std::array<std::string, 3> expectedRowPatern;
};

TEST_P(ConsoleDisplayTestSuite_CheckRows, rowMatchesGivenPatern)
{
    for (auto initialField : initialFields)
        sut.field(initialField.first) = initialField.second;

    sut.update();

    EXPECT_THAT(stream.str(), matches(expectedRowPatern));
}

INSTANTIATE_TEST_CASE_P(containsCharacterInSpecifiedRow, ConsoleDisplayTestSuite_CheckRows, Values(
    CheckRowsParams({{Position(7), ::Field::X}}, {"X", "", ""}),
    CheckRowsParams({{Position(5), ::Field::X}}, {"", "X", ""}),
    CheckRowsParams({{Position(3), ::Field::X}}, {"", "", "X"})
));

INSTANTIATE_TEST_CASE_P(containsCharactersInSpecifiedOrder, ConsoleDisplayTestSuite_CheckRows, Values(
    CheckRowsParams({{Position(7), ::Field::X}, {Position(9), ::Field::O}}, {"X.* .*O", "", ""}),
    CheckRowsParams({{Position(5), ::Field::O}, {Position(4), ::Field::X}}, {"", "X.*O.* ", ""}),
    CheckRowsParams({{Position(3), ::Field::X}, {Position(2), ::Field::O}}, {"", "", " .*O.*X"})
));

