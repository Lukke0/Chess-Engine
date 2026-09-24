#include "FEN.h"

#include <stdexcept>

namespace
{
    bool is_piece(char c)
    {
        return c != '\0' && std::string("prnbqkPRNBQK").find(c) != std::string::npos;
    }
}

FEN::Placement FEN::parse(std::string const& code)
{
    Placement placement{};
    int x = 0, y = 0;
    for (char c : code)
    {
        if (c == ' ')
            break;
        if (c == '/')
        {
            if (x != 8 || y == 7)
                throw std::invalid_argument("Invalid rank in FEN code");
            x = 0;
            ++y;
        }
        else if (c >= '1' && c <= '8')
        {
            x += c - '0';
            if (x > 8)
                throw std::invalid_argument("Too many squares in FEN rank");
        }
        else
        {
            if (!is_piece(c) || x >= 8)
                throw std::invalid_argument("Invalid piece or rank in FEN code");
            placement[y][x++] = c;
        }
    }
    if (y != 7 || x != 8)
        throw std::invalid_argument("FEN placement must contain eight complete ranks");
    return placement;
}

