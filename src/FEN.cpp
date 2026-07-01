#include "FEN.h"

#include <cctype>
#include <iostream>
#include <stdexcept>

namespace
{
    // Small helper so each piece type is a single line in the switch below.
    template <typename T>
    std::unique_ptr<Piece> make(std::pair<int, int> pos, int window_size, bool white)
    {
        return std::make_unique<T>(pos, window_size, white);
    }
}

std::unique_ptr<Piece> FEN::create_piece(std::pair<int, int> pos, char c, int window_size)
{
    bool const white = std::isupper(static_cast<unsigned char>(c)) != 0;

    switch (std::tolower(static_cast<unsigned char>(c)))
    {
    case 'p': return make<Pawn>  (pos, window_size, white);
    case 'r': return make<Rook>  (pos, window_size, white);
    case 'n': return make<Knight>(pos, window_size, white);
    case 'b': return make<Bishop>(pos, window_size, white);
    case 'q': return make<Queen> (pos, window_size, white);
    default:
        std::cout << c << std::endl;
        throw std::logic_error("Invalid letter in FEN code");
    }
}

std::vector<std::unique_ptr<Piece>> FEN::parse(std::string const& code, int window_size)
{
    //TODO: Lägg in felläsning av FENkod
    std::cout << "Reading FEN: " << code << std::endl;

    std::vector<std::unique_ptr<Piece>> pieces;
    int x{}, y{};

    for (char const c : code)
    {
        // The piece-placement field ends at the first space; ignore the rest.
        if (c == ' ')
        {
            break;
        }
        else if (c == '/')
        {
            std::cout << "New Line detected.\n";
            x = 0;
            y++;
        }
        else if (std::isdigit(static_cast<unsigned char>(c)))
        {
            if (c < 1 || c > 8)
            {
                throw std::logic_error("Invalid digit in FEN code");
                break;
            }
            std::cout << "blank space added: " << c << std::endl;
            x += c - '0';
        }
        else
        {
            std::cout << "Creating piece " << c << ". at: " << x << ", " << y << std::endl;
            pieces.push_back(create_piece({ x, y }, c, window_size));
            x++;
        }
    }

    return pieces;
}
