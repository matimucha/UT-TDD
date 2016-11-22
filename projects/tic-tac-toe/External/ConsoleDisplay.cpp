#include "ConsoleDisplay.hpp"
#include <vector>

namespace
{
    std::string to_string(Field field)
    {
        switch(field)
        {
            case Field::Blank: return " ";
            case Field::X: return "X";
            case Field::O: return "O";
        }
    }
}

ConsoleDisplay::ConsoleDisplay(std::ostream& outputStream)
    : out(outputStream)
{
}

Field& ConsoleDisplay::field(const Position& pos)
{
    return fields[static_cast<size_t>(pos)-1];
}

Field ConsoleDisplay::field(const Position& pos) const
{
    return fields[static_cast<size_t>(pos)-1];
}

void ConsoleDisplay::update() const
{
    using RowIndexes = std::initializer_list<std::initializer_list<int>>;
    const RowIndexes rows = {
        { 7, 8, 9 },
        { 4, 5, 6 },
        { 1, 2, 3 } };
    for (const auto& row : rows)
    {
        out << "|";
        for (const auto& pos : row)
            out << to_string(field(Position(pos))) << "|";
        out << std::endl;
    }
}
