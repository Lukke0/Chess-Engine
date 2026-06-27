#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<SFML/System.hpp>

#include "piece.h"

#include<iostream>
#include<vector>
#include<memory>

//Global variables.
bool clicked{ false };
int window_size{ 800 };
std::vector<std::unique_ptr<Piece>> pieces;
std::string start_pos("rnbq1bnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQ1BNR");
std::string pos("5Q2/8/5P2/4k3/6K1/8/8/1B6 b - - 0 71");

void Draw_board(sf::RenderWindow & window)
{
    sf::RectangleShape square{ sf::Vector2f(window.getSize().x / 8, window.getSize().y / 8)};

    for (size_t i = 0; i < 8; i++)
    {
        for (size_t j = 0; j < 8; j++)
        {
            square.setPosition(j * (window.getSize().x / 8), i * (window.getSize().y / 8));

            if ((i + j) % 2 == 0)
            {
                square.setFillColor(sf::Color::White);
            }
            else
            {
                square.setFillColor(sf::Color(70, 70, 70));
            }
            window.draw(square);
        }
    }
}
void Highlight(sf::RenderWindow& window)
{
    sf::Vector2i MousePos = sf::Mouse::getPosition(window);

    int square_pos_x{ static_cast<int>(MousePos.x / (window.getSize().x / 8)) };
    int square_pos_y{ static_cast<int>(MousePos.y / (window.getSize().y / 8)) };

    if (window.hasFocus())
    { 
        sf::RectangleShape square{ sf::Vector2f(window.getSize().x / 8, window.getSize().y / 8) };

        square.setFillColor(sf::Color(255, 0, 0, 64));
        square.setPosition(square_pos_x * (window.getSize().y / 8), square_pos_y * (window.getSize().y / 8));
        window.draw(square);
    }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && clicked == false)
    {
        std::cout << "click at: " << square_pos_x << ", " << square_pos_y << std::endl;
        clicked = true;
    }

    if (!sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
    {
        clicked = false;
    }
}

void create_piece(std::pair<int, int> pos, char const& c)
{
  
    switch (c)
    {
    case 'p':
        pieces.push_back(std::make_unique<Pawn>(pos, window_size, false)); // black
        break;
    case 'P':
        pieces.push_back(std::make_unique<Pawn>(pos, window_size, true));  // white
        break;
    case 'r':
        pieces.push_back(std::make_unique<Rook>(pos, window_size, false));
        break;
    case 'R':
        pieces.push_back(std::make_unique<Rook>(pos, window_size, true));
        break;
    case 'n':
        pieces.push_back(std::make_unique<Knight>(pos, window_size, false));
        break;
    case 'N':
        pieces.push_back(std::make_unique<Knight>(pos, window_size, true));
        break;
    case 'b':
        pieces.push_back(std::make_unique<Bishop>(pos, window_size, false));
        break;
    case 'B':
        pieces.push_back(std::make_unique<Bishop>(pos, window_size, true));
        break;
    case 'q':
        pieces.push_back(std::make_unique<Queen>(pos, window_size, false));
        break;
    case 'Q':
        pieces.push_back(std::make_unique<Queen>(pos, window_size, true));
        break;
    default:
        std::cout << c << std::endl;
        throw std::logic_error("Invalid letter in FEN code");
        break;
    }
}

void readFEN(std::string const& code)
{   
    //TODO: Lägg in felläsning av FENkod
    std::cout << "Reading FEN: " << code << std::endl;
    int x{}, y{};
    for_each(code.begin(), code.end(), 
        [&x, &y](char const& c) 
        {
            if (c == '/')
            {
                std::cout << "New Line detected.\n";
                x = 0;
                y++;
            }
            else if (isdigit(c))
            {
                std::cout << "blank space added: " << c << std::endl;
                x += c - '0';
            }
            else
            {
                std::cout << "Creating piece " << c << ". at: " << x << ", " << y << std::endl;
                create_piece({ x, y }, c); 
                x++;
            }
        });
}

int main()
{
    readFEN(start_pos);
    sf::RenderWindow window(sf::VideoMode(window_size, window_size), "Chess Program");
    window.setFramerateLimit(30);
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        Draw_board(window);
        Highlight(window);

        for (auto const& e : pieces)
        {
            window.draw(e->get_sprite());
        }

        window.display();
    }
    return 0;
}