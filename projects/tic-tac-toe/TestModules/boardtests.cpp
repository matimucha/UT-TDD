#include <gmock/gmock.h>
#include <array>
#include "../External/Interfaces/Field.hpp"
#include "../External/Interfaces/Position.hpp"


class Board
{
    private:
        std::array<Field, 10> _fields;
    public:
        Board() {}
        uint freeFieldsCount()
        {
            return 9;
        }
        bool isWon()
        {
            return (_fields.at(1) == _fields.at(2) && _fields.at(2) == _fields.at(3));
        }

        bool isDraw()
        {
            return false;
        }

        void setField(Position pos, Field field)
        {
            _fields.at(static_cast<size_t>(pos)) = field;
        }

};

TEST(boardTests, newBoardIsNotWon) //first test to ensure result of the game
{
    Board board;
    ASSERT_THAT(board.isWon(), testing::Eq(false) );
}

TEST(boardTests, newBoardIsDraw) //second test to ensure result of the game
{
    Board board;
    ASSERT_THAT(board.isDraw(), testing::Eq(false) );
}

TEST(boardTests, newBoardAllFreeFields)
{
    Board board;
    ASSERT_THAT(board.freeFieldsCount(), testing::Eq(9) );
}

TEST(boardTests, isAnyPlayerWinner)
{
    Board board;

    board.setField(Position(1), Field::X);
    board.setField(Position(2), Field::X);

    board.setField(Position(3), Field::X);

    ASSERT_THAT(board.isWon(), testing::Eq(true) );
}
