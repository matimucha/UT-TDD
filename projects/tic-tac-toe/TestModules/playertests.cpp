#include <gmock/gmock.h>
#include "../External/Interfaces/Field.hpp"

//TEST_F

//without test suite running TEST without _F

//check if our move will appear on screen

class Player
{
    public:
        Player(Field symb) : symbol{ symb } {}
        Field getSymbol()
        {
            return symbol;
        }
    Field symbol;
};

TEST(playerTest, symbolIsEqualToX) //check if sign type responds to player
{
    Field symbol { Field::X };
    Player player { symbol };
    ASSERT_THAT(player.getSymbol(), testing::Eq(symbol));
}


TEST(playerTest, symbolIsEqualToO) //check if sign type responds to player
{
    Field symbol { Field::O };
    Player player { symbol };
    ASSERT_THAT(player.getSymbol(), testing::Eq(symbol));
}
