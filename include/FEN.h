#ifndef FEN_H
#define FEN_H

#include "piece.h"

#include <memory>
#include <string>
#include <utility>
#include <vector>

// Parses the piece-placement part of a FEN string and builds the pieces.
class FEN
{
public:
    // Reads a FEN code and returns the pieces on the board.
    // window_size is needed to position and scale each piece's sprite.
    static std::vector<std::unique_ptr<Piece>> parse(std::string const& code, int window_size);

private:
    // Creates a single piece from a FEN letter at the given board position.
    static std::unique_ptr<Piece> create_piece(std::pair<int, int> pos, char c, int window_size);
};

#endif
