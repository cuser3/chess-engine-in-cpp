#include <iostream>
#include <string>
#include "chessengine.h"
#include <set>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

using namespace std;

sf::Sprite createSprite(std::string texturePath, sf::Texture &texture, float squareSize)
{
    if (!texture.loadFromFile(texturePath))
    {
        std::cerr << "Error: Could not load texture from " << texturePath << std::endl;
        exit(1);
    }
    sf::Sprite sprite(texture);
    sprite.setScale(sf::Vector2f(squareSize / texture.getSize().x, squareSize / texture.getSize().y));
    return sprite;
}

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
    sf::Sprite whitePawn = createSprite("Assets/white-pawn.png", whitePawnTexture, squareSize);

    sf::Texture blackPawnTexture;
    sf::Sprite blackPawn = createSprite("Assets/black-pawn.png", blackPawnTexture, squareSize);

    // Rooks
    sf::Texture whiteRookTexture;
    sf::Sprite whiteRook = createSprite("Assets/white-rook.png", whiteRookTexture, squareSize);

    sf::Texture blackRookTexture;
    sf::Sprite blackRook = createSprite("Assets/black-rook.png", blackRookTexture, squareSize);

    // Knights
    sf::Texture whiteKnightTexture;
    sf::Sprite whiteKnight = createSprite("Assets/white-knight.png", whiteKnightTexture, squareSize);

    sf::Texture blackKnightTexture;
    sf::Sprite blackKnight = createSprite("Assets/black-knight.png", blackKnightTexture, squareSize);

    // Bishops
    sf::Texture whiteBishopTexture;
    sf::Sprite whiteBishop = createSprite("Assets/white-bishop.png", whiteBishopTexture, squareSize);

    sf::Texture blackBishopTexture;
    sf::Sprite blackBishop = createSprite("Assets/black-bishop.png", blackBishopTexture, squareSize);

    // Queens
    sf::Texture whiteQueenTexture;
    sf::Sprite whiteQueen = createSprite("Assets/white-queen.png", whiteQueenTexture, squareSize);

    sf::Texture blackQueenTexture;
    sf::Sprite blackQueen = createSprite("Assets/black-queen.png", blackQueenTexture, squareSize);

    // Kings
    sf::Texture whiteKingTexture;
    sf::Sprite whiteKing = createSprite("Assets/white-king.png", whiteKingTexture, squareSize);

    sf::Texture blackKingTexture;
    sf::Sprite blackKing = createSprite("Assets/black-king.png", blackKingTexture, squareSize);

    // Create the main window
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Chess Engine");
    window.setVerticalSyncEnabled(true);

    // Run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();

            // Handle mouse button presses
            if (const auto* mouseButtonpressed = event->getIf<sf::Event::MouseButtonPressed>())
            {
                if (mouseButtonpressed->button == sf::Mouse::Button::Left)
                {
                    std::cout << "Left Mouse Button Pressed" << std::endl;
                    std::cout << "mouse x: " << mouseButtonpressed->position.x << std::endl;
                    std::cout << "mouse y: " << mouseButtonpressed->position.y << std::endl;
                }
            }
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