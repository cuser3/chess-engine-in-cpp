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
    const float squareSize = 60.f;
    const sf::Color lightColor = sf::Color(240, 217, 181);
    const sf::Color darkColor = sf::Color(181, 136, 99);

    // Pawns
    sf::Texture whitePawnTexture;
    if (!whitePawnTexture.loadFromFile("Assets/white-pawn.png"))
    {
        std::cerr << "Error: Could not load white pawn texture!" << std::endl;
        return 1;
    }
    sf::Sprite whitePawn = sf::Sprite(whitePawnTexture);
    whitePawn.setScale(sf::Vector2f(squareSize / whitePawnTexture.getSize().x, squareSize / whitePawnTexture.getSize().y));

    sf::Texture blackPawnTexture;
    if (!blackPawnTexture.loadFromFile("Assets/black-pawn.png"))
    {
        std::cerr << "Error: Could not load white pawn texture!" << std::endl;
        return 1;
    }
    sf::Sprite blackPawn = sf::Sprite(blackPawnTexture);
    blackPawn.setScale(sf::Vector2f(squareSize / blackPawnTexture.getSize().x, squareSize / blackPawnTexture.getSize().y));

    // Rooks
    sf::Texture whiteRookTexture;
    if (!whiteRookTexture.loadFromFile("Assets/white-rook.png"))
    {
        std::cerr << "Error: Could not load white rook texture!" << std::endl;
        return 1;
    }
    sf::Sprite whiteRook = sf::Sprite(whiteRookTexture);
    whiteRook.setScale(sf::Vector2f(squareSize / whiteRookTexture.getSize().x, squareSize / whiteRookTexture.getSize().y));

    sf::Texture blackRookTexture;
    if (!blackRookTexture.loadFromFile("Assets/black-rook.png"))
    {
        std::cerr << "Error: Could not load white rook texture!" << std::endl;
        return 1;
    }
    sf::Sprite blackRook = sf::Sprite(blackRookTexture);
    blackRook.setScale(sf::Vector2f(squareSize / blackRookTexture.getSize().x, squareSize / blackRookTexture.getSize().y));


    // Knights
    sf::Texture whiteKnightTexture;
    if (!whiteKnightTexture.loadFromFile("Assets/white-knight.png"))
    {
        std::cerr << "Error: Could not load white knight texture!" << std::endl;
        return 1;
    }
    sf::Sprite whiteKnight = sf::Sprite(whiteKnightTexture);
    whiteKnight.setScale(sf::Vector2f(squareSize / whiteKnightTexture.getSize().x, squareSize / whiteKnightTexture.getSize().y));

    sf::Texture blackKnightTexture;
    if (!blackKnightTexture.loadFromFile("Assets/black-knight.png"))
    {
        std::cerr << "Error: Could not load white rook texture!" << std::endl;
        return 1;
    }
    sf::Sprite blackKnight = sf::Sprite(blackKnightTexture);
    blackKnight.setScale(sf::Vector2f(squareSize / blackKnightTexture.getSize().x, squareSize / blackKnightTexture.getSize().y));


    // Bishops
    sf::Texture whiteBishopTexture;
    if (!whiteBishopTexture.loadFromFile("Assets/white-bishop.png"))
    {
        std::cerr << "Error: Could not load white bishop texture!" << std::endl;
        return 1;
    }
    sf::Sprite whiteBishop = sf::Sprite(whiteBishopTexture);
    whiteBishop.setScale(sf::Vector2f(squareSize / whiteBishopTexture.getSize().x, squareSize / whiteBishopTexture.getSize().y));

    sf::Texture blackBishopTexture;
    if (!blackBishopTexture.loadFromFile("Assets/black-bishop.png"))
    {
        std::cerr << "Error: Could not load black bishop texture!" << std::endl;
        return 1;
    }
    sf::Sprite blackBishop = sf::Sprite(blackBishopTexture);
    blackBishop.setScale(sf::Vector2f(squareSize / blackBishopTexture.getSize().x, squareSize / blackBishopTexture.getSize().y));

    // Queens
    sf::Texture whiteQueenTexture;
    if (!whiteQueenTexture.loadFromFile("Assets/white-queen.png"))
    {
        std::cerr << "Error: Could not load white queen texture!" << std::endl;
        return 1;
    }
    sf::Sprite whiteQueen = sf::Sprite(whiteQueenTexture);
    whiteQueen.setScale(sf::Vector2f(squareSize / whiteQueenTexture.getSize().x, squareSize / whiteQueenTexture.getSize().y));

    sf::Texture blackQueenTexture;
    if (!blackQueenTexture.loadFromFile("Assets/black-queen.png"))
    {
        std::cerr << "Error: Could not load black queen texture!" << std::endl;
        return 1;
    }
    sf::Sprite blackQueen = sf::Sprite(blackQueenTexture);
    blackQueen.setScale(sf::Vector2f(squareSize / blackQueenTexture.getSize().x, squareSize / blackQueenTexture.getSize().y));

    // Kings
    sf::Texture whiteKingTexture;
    if (!whiteKingTexture.loadFromFile("Assets/white-king.png"))
    {
        std::cerr << "Error: Could not load white king texture!" << std::endl;
        return 1;
    }
    sf::Sprite whiteKing = sf::Sprite(whiteKingTexture);
    whiteKing.setScale(sf::Vector2f(squareSize / whiteKingTexture.getSize().x, squareSize / whiteKingTexture.getSize().y));
    
    sf::Texture blackKingTexture;
    if (!blackKingTexture.loadFromFile("Assets/black-king.png"))
    {
        std::cerr << "Error: Could not load black king texture!" << std::endl;
        return 1;
    }
    sf::Sprite blackKing = sf::Sprite(blackKingTexture);
    blackKing.setScale(sf::Vector2f(squareSize / blackKingTexture.getSize().x, squareSize / blackKingTexture.getSize().y));






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
        for (int row = 0; row < boardSize; ++row)
        {
            for (int col = 0; col < boardSize; ++col)
            {
                sf::RectangleShape square(sf::Vector2f(squareSize, squareSize));
                square.setPosition(sf::Vector2f(col * squareSize, row * squareSize));

                if ((row + col) % 2 == 0)
                    square.setFillColor(lightColor);

                else
                    square.setFillColor(darkColor);
                window.draw(square);

                // Draw pieces
                if (row == 0 || row == 7)
                {
                    if (col == 0 || col == 7)
                    {
                        if (row == 0)
                        {
                            blackRook.setPosition(sf::Vector2f(col * squareSize, row * squareSize));
                            window.draw(blackRook);
                        }
                        else
                        {
                            whiteRook.setPosition(sf::Vector2f(col * squareSize, row * squareSize));
                            window.draw(whiteRook);
                        }
                    }
                    if (col == 1 || col == 6)
                    {
                        if (row == 0)
                        {
                            blackKnight.setPosition(sf::Vector2f(col * squareSize, row * squareSize));
                            window.draw(blackKnight);
                        }
                        else
                        {
                            whiteKnight.setPosition(sf::Vector2f(col * squareSize, row * squareSize));
                            window.draw(whiteKnight);
                        }
                    }
                    if (col == 2 || col == 5)
                    {
                        if (row == 0)
                        {
                            blackBishop.setPosition(sf::Vector2f(col * squareSize, row * squareSize));
                            window.draw(blackBishop);
                        }
                        else
                        {
                            whiteBishop.setPosition(sf::Vector2f(col * squareSize, row * squareSize));
                            window.draw(whiteBishop);
                        }
                    }
                    if (col == 3)
                    {
                        if (row == 0)
                        {
                            blackQueen.setPosition(sf::Vector2f(col * squareSize, row * squareSize));
                            window.draw(blackQueen);
                        }
                        else
                        {
                            whiteQueen.setPosition(sf::Vector2f(col * squareSize, row * squareSize));
                            window.draw(whiteQueen);
                        }
                    }
                    if (col == 4)
                    {
                        if (row == 0)
                        {
                            blackKing.setPosition(sf::Vector2f(col * squareSize, row * squareSize));
                            window.draw(blackKing);
                        }
                        else
                        {
                            whiteKing.setPosition(sf::Vector2f(col * squareSize, row * squareSize));
                            window.draw(whiteKing);
                        }
                    }
                }

                if (row == 1)
                {
                    blackPawn.setPosition(sf::Vector2f(col * squareSize, row * squareSize));
                    window.draw(blackPawn);
                }

                if (row == 6)
                {
                    whitePawn.setPosition(sf::Vector2f(col * squareSize, row * squareSize));
                    window.draw(whitePawn);
                }
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