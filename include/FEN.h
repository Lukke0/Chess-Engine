#ifndef FEN_H
#define FEN_H

#include <array>
#include <string>

// Converts the piece-placement field only; other FEN fields are ignored.
class FEN
{
public:
    // Indexed [y][x], with a8 at [0][0]. A null character is an empty square.
    using Placement = std::array<std::array<char, 8>, 8>;

    static Placement parse(std::string const& code);
};

#endif
