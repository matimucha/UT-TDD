#include <gmock/gmock.h>
#include <array>
#include "../External/Interfaces/Field.hpp"
#include "../External/Interfaces/Position.hpp"


class Board
{
    private:
        std::array<Field, 10> _fields;
    public:
        Board()
        {
            std::fill(_fields.begin(), _fields.end(), Field::Blank);
        }

        uint freeFieldsCount()
        {
            int _checkField = 0;
            for(int i = 0; i < _fields.size(); ++i)
            {
                if(_fields.at(i) == Field::Blank)
                    ++_checkField;
            }
            return (_checkField -1);
        }

        bool isWon()
        {
            return (_fields.at(1) == _fields.at(2) && _fields.at(2) == _fields.at(3)
                    && _fields.at(1) != Field::Blank && _fields.at(2) != Field::Blank
                    && _fields.at(3) != Field::Blank);
        }

        bool isDraw()
        {
            return (this->freeFieldsCount() == 0 && !(this->isWon()));
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

TEST(boardTests, isPlayerXWinnerAtRow)
{
    Board board;

    board.setField(Position(1), Field::X);
    board.setField(Position(2), Field::X);

    board.setField(Position(3), Field::X);

    ASSERT_THAT(board.isWon(), testing::Eq(true) );
}

TEST(boardTests, isPlayerOWinnerAtRow)
{
    Board board;

    board.setField(Position(1), Field::O);
    board.setField(Position(2), Field::O);

    board.setField(Position(3), Field::O);

    ASSERT_THAT(board.isWon(), testing::Eq(true) );
}

TEST(boardTests, isDrawAtEnd)
{
    Board board;
    for(int i = 0; i < 9; ++i) //genration of random signs on board
    {
        if(i%2)
            board.setField(Position(i+1), Field::X);
        else
            board.setField(Position(i+1), Field::O);
    }
    ASSERT_THAT(board.isDraw(), testing::Eq(true));
}

TEST(boardTests, isAllBoardFilled)
{
    Board board;
    for(int i = 0; i < 9; ++i) //genration of random signs on board
    {
        if(i%2)
            board.setField(Position(i+1), Field::X);
        else
            board.setField(Position(i+1), Field::O);
    }
    ASSERT_THAT(board.freeFieldsCount(), testing::Eq(0) );
}
