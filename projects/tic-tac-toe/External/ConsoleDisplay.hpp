#pragma once

#include "Interfaces/Display.hpp"
#include <iostream>
#include <array>

class ConsoleDisplay : public Display
{
public:
    explicit ConsoleDisplay(std::ostream& outputStream = std::cout);

    Field& field(const Position&) override;
    Field field(const Position&) const override;
    void update() const override;

private:
    std::ostream& out;

    std::array<Field, 9> fields {};
};
