#include "piece.h"
#include <stdexcept>
#include <SFML/Graphics.hpp>

// Constructor for Piece
Piece::Piece(std::pair<int, int> const& start, int const _size, int const v)
    : position{}, window_size{ _size }, value{ v }
{
    if (start.first >= 0 && start.first < 8 && start.second >= 0 && start.second < 8)
    {
        // Put piece into correct position
        position = start;
        set_position(position);
    }
    else
    {
        throw std::logic_error("incorrect placement of piece");
    }
}

// Set position of piece on board
void Piece::set_position(std::pair<int, int> const& new_pos)
{
    my_sprite.setPosition(
        new_pos.first * (window_size / 8),
        new_pos.second * (window_size / 8)
    );
}

// Set and scale texture to fit square
void Piece::set_texture(sf::Texture const& t)
{
    my_sprite.setTexture(t);

    sf::Vector2u tex_size{ t.getSize() };
    float square_size{ static_cast<float>(window_size) / 8.0f };

    my_sprite.setScale(
        square_size / tex_size.x,
        square_size / tex_size.y
    );
}

// Constructor for Pawn
Pawn::Pawn(std::pair<int, int> const& start, int const _size, int const v)
    : Piece{ start, _size, v }
{
    if (!texture.loadFromFile("assets/Chess_pawn_black.png"))
    {
        throw std::runtime_error("Could not load pawn_b texture");
    }

    set_texture(texture);
    set_position(start); // Ensure correct positioning after setting texture
}
