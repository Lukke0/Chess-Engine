#ifndef PIECE_H
#define PIECE_H

#include<SFML/Graphics.hpp>

class Piece
{
public:
	Piece(std::pair<int, int> const& start, int const _size, int const v, bool const white);

	void set_position(std::pair<int, int> const& new_pos);
	void set_texture(sf::Texture const& t);
	sf::Sprite const& get_sprite() const;

protected:
	std::pair<int, int> position{ 0, 0 };
	int window_size, value;
	sf::Sprite my_sprite{};
	bool white{ false };
};

class Pawn : public Piece
{
public:

	Pawn(std::pair<int, int> const& start, int const _size, bool const white);

private:
	sf::Texture texture;
};

class Rook : public Piece
{
public:
	Rook(std::pair<int, int> const& start, int const _size, bool const white);

private:
	sf::Texture texture;
};

class Knight : public Piece
{
public:
	Knight(std::pair<int, int> const& start, int const _size, bool const white);

private:
	sf::Texture texture;
};

class Bishop : public Piece
{
public:	
	Bishop(std::pair<int, int> const& start, int const _size, bool const white);

private:
	sf::Texture texture;
};

class Queen : public Piece
{
public:
	Queen(std::pair<int, int> const& start, int const _size, bool const white);

private:
	sf::Texture texture;
};
#endif