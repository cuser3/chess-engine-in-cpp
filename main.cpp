#include <iostream>
#include <string>
#include "chessengine.h"
#include <set>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

using namespace std;

int main()
{
    GameState gamestate;

    string move;

    const int boardSize = 8;
    const float squareSize = 60.f; // Size of each square in pixels
    const sf::Color lightColor = sf::Color(240, 217, 181); // Light square color
    const sf::Color darkColor = sf::Color(181, 136, 99);   // Dark square color

    sf::RenderWindow window(sf::VideoMode({800, 600}), "Chess Engine");
    window.setVerticalSyncEnabled(true);

    // run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        while (const std::optional event = window.pollEvent())
        {
            // "close requested" event: we close the window
            if (event->is<sf::Event::Closed>())
                window.close();
        }
        // clear the window with black color
        window.clear(sf::Color::Black);

        // Draw chessboard
        for (int row = 0; row < boardSize; ++row) {
            for (int col = 0; col < boardSize; ++col) {
                sf::RectangleShape square(sf::Vector2f(squareSize, squareSize));
                square.setPosition(sf::Vector2f(col * squareSize, row * squareSize));
                if ((row + col) % 2 == 0)
                    square.setFillColor(lightColor);
                else
                    square.setFillColor(darkColor);
                window.draw(square);
            }
        }

        // end the current frame
        window.display();
    }

    // while (true)
    // {
    //     gamestate.displayBoard();
    //     set<string> validMoves = gamestate.getValidMoves();
    //     for (auto &move : validMoves) {
    //         cout << "Move: " << move;
    //     }
    //     cout << "Enter your move (e.g., e2e4) or 'q' to quit: " << endl;
    //     cin >> move;

    //     if (move == "q")
    //     {
    //         break;
    //     }

    //     if (validMoves.count(move))
    //     {
    //         gamestate.makeMove(move);
    //     }
    //     else
    //     {
    //         cout << "Invalid move. Please try again." << endl;
    //     }
    // }
    return 0;
}