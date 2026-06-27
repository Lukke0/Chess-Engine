#include "include/piece.h"
#include <stdexcept>
#include <SFML/Graphics.hpp>

// Constructor for Piece
Piece::Piece(std::pair<int, int> const& start, int const _size, int const v, bool const white)
    : position{}, window_size{ _size }, value{ v }, white { white }
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
        new_pos.first * (window_size / 8) - 1.f,
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

sf::Sprite const& Piece::get_sprite() const
{
    return my_sprite;
}

// Constructor for Pawn
Pawn::Pawn(std::pair<int, int> const& start, int const _size, bool const white)
    : Piece{ start, _size, 1 , white}
{
    if (white)
    {
        if (!texture.loadFromFile("assets/Chess_pawn_white.png"))
        {
            throw std::runtime_error("Could not load pawn_w texture");
        }
    }
    else
    {
        if (!texture.loadFromFile("assets/Chess_pawn_black.png"))
        {
            throw std::runtime_error("Could not load pawn_b texture");
        }
    }
    set_texture(texture);
}

Rook::Rook(std::pair<int, int> const& start, int const _size, bool const white)
    : Piece { start, _size, 5, white }
{ 
    if (white)
    {
        if (!texture.loadFromFile("assets/Chess_rook_white.png"))
        {
            throw std::runtime_error("Could not load rook_w texture");
        }
    }
    else
    {
        if (!texture.loadFromFile("assets/Chess_rook_black.png"))
        {
            throw std::runtime_error("Could not load rook_b texture");
        }
    }
    set_texture(texture);
}

Knight::Knight(std::pair<int, int> const& start, int const _size, bool const white)
    : Piece{ start, _size, 3, white }
{
    if (white)
    {
        if (!texture.loadFromFile("assets/Chess_knight_white.png"))
        {
            throw std::runtime_error("Could not load rook_w texture");
        }
    }
    else
    {
        if (!texture.loadFromFile("assets/Chess_knight_black.png"))
        {
            throw std::runtime_error("Could not load rook_b texture");
        }
    }
    set_texture(texture);
}

Bishop::Bishop(std::pair<int, int> const& start, int const _size, bool const white)
    : Piece{ start, _size, 3, white }
{
    if (white)
    {
        if (!texture.loadFromFile("assets/Chess_bishop_white.png"))
        {
            throw std::runtime_error("Could not load bishop_w texture");
        }
    }
    else
    {
        if (!texture.loadFromFile("assets/Chess_bishop_black.png"))
        {
            throw std::runtime_error("Could not load bishop_b texture");
        }
    }
    set_texture(texture);
}

Queen::Queen(std::pair<int, int> const& start, int const _size, bool const white)
    : Piece{ start, _size, 3, white }
{
    if (white)
    {
        if (!texture.loadFromFile("assets/Chess_queen_white.png"))
        {
            throw std::runtime_error("Could not load queen_w texture");
        }
    }
    else
    {
        if (!texture.loadFromFile("assets/Chess_queen_black.png"))
        {
            throw std::runtime_error("Could not load queen_b texture");
        }
    }
    set_texture(texture);
}