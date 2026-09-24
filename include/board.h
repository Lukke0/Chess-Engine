
#pragma once

#include<piece.h>
#include <memory>
#include <vector>
#include <string>

class Board
{
public:

Board(std::string const& fen, int window_size);

void draw(sf::RenderWindow& window);

private:

void set_board(std::string const& fen);

Piece* Chess_board[8][8]{};
int window_size;
std::unique_ptr<Piece> create_piece(int x, int y, char symbol) const;
std::vector<std::unique_ptr<Piece>> pieces;

};
