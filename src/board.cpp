#include "board.h"
#include "FEN.h"

#include <cctype>
#include <stdexcept>
#include <utility>

Board::Board(std::string const& fen, int window_size)
 : window_size{ window_size }
{
    set_board(fen);
}

void Board::set_board(std::string const& fen)
{
    FEN::Placement const placement = FEN::parse(fen);

    for (int y = 0; y < 8; ++y)
    {
        for (int x = 0; x < 8; ++x)
        {
            char const symbol = placement[y][x];
            if (symbol != '\0')
            {
                std::unique_ptr<Piece> piece = create_piece(x, y, symbol);
                Chess_board[x][y] = piece.get();
                pieces.push_back(std::move(piece));
            }
        }
    }
}

std::unique_ptr<Piece> Board::create_piece(int x, int y, char symbol) const
{
    bool const white = std::isupper(static_cast<unsigned char>(symbol)) != 0;
    std::pair<int, int> const pos{x, y};
    switch (std::tolower(static_cast<unsigned char>(symbol)))
    {
    case 'p': return std::make_unique<Pawn>(pos, window_size, white);
    case 'r': return std::make_unique<Rook>(pos, window_size, white);
    case 'n': return std::make_unique<Knight>(pos, window_size, white);
    case 'b': return std::make_unique<Bishop>(pos, window_size, white);
    case 'q': return std::make_unique<Queen>(pos, window_size, white);
    case 'k': return std::make_unique<King>(pos, window_size, white);
    default: throw std::invalid_argument("Invalid piece symbol");
    }
}

void Board::draw(sf::RenderWindow& window)
{
    for (int y = 0; y < 8; ++y)
    {
        for (int x = 0; x < 8; ++x)
        {
            if (Chess_board[x][y] != nullptr)
            {
                window.draw(Chess_board[x][y]->get_sprite());
            }
        }
    }
}


