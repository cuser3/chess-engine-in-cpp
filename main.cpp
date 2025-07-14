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

    bool pieceSelected = false;
    std::pair<int, int> selectedSquare = {-1, -1};

    std::set<std::pair<int, int>> possibleMoves;

    // Pawns
    sf::Texture whitePawnTexture;
    sf::Sprite whitePawn = createSprite("assets/white-pawn.png", whitePawnTexture, squareSize);

    sf::Texture blackPawnTexture;
    sf::Sprite blackPawn = createSprite("assets/black-pawn.png", blackPawnTexture, squareSize);

    // Rooks
    sf::Texture whiteRookTexture;
    sf::Sprite whiteRook = createSprite("assets/white-rook.png", whiteRookTexture, squareSize);

    sf::Texture blackRookTexture;
    sf::Sprite blackRook = createSprite("assets/black-rook.png", blackRookTexture, squareSize);

    // Knights
    sf::Texture whiteKnightTexture;
    sf::Sprite whiteKnight = createSprite("assets/white-knight.png", whiteKnightTexture, squareSize);

    sf::Texture blackKnightTexture;
    sf::Sprite blackKnight = createSprite("assets/black-knight.png", blackKnightTexture, squareSize);

    // Bishops
    sf::Texture whiteBishopTexture;
    sf::Sprite whiteBishop = createSprite("assets/white-bishop.png", whiteBishopTexture, squareSize);

    sf::Texture blackBishopTexture;
    sf::Sprite blackBishop = createSprite("assets/black-bishop.png", blackBishopTexture, squareSize);

    // Queens
    sf::Texture whiteQueenTexture;
    sf::Sprite whiteQueen = createSprite("assets/white-queen.png", whiteQueenTexture, squareSize);

    sf::Texture blackQueenTexture;
    sf::Sprite blackQueen = createSprite("assets/black-queen.png", blackQueenTexture, squareSize);

    // Kings
    sf::Texture whiteKingTexture;
    sf::Sprite whiteKing = createSprite("assets/white-king.png", whiteKingTexture, squareSize);

    sf::Texture blackKingTexture;
    sf::Sprite blackKing = createSprite("assets/black-king.png", blackKingTexture, squareSize);

    // Create the main window
    sf::RenderWindow window(sf::VideoMode({480, 480}), "Chess Engine");
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
            if (const auto *mouseButtonpressed = event->getIf<sf::Event::MouseButtonPressed>())
            {
                if (mouseButtonpressed->button == sf::Mouse::Button::Left)
                {
                    int col = static_cast<int>(mouseButtonpressed->position.x / squareSize);
                    int row = static_cast<int>(mouseButtonpressed->position.y / squareSize);

                    if (!pieceSelected)
                    {
                        if (gamestate.board[row][col] != "--")
                        {
                            selectedSquare = {col, row};
                            pieceSelected = true;

                            // highlighting possible moves for selected piece
                            possibleMoves.clear();
                            std::set<std::string> validMoves = gamestate.getValidMoves();
                            for (const auto &moveStr : validMoves)
                            {
                                int startRow = 7 - (moveStr[1] - '1');
                                int startCol = moveStr[0] - 'a';
                                int endRow = 7 - (moveStr[3] - '1');
                                int endCol = moveStr[2] - 'a';
                                if (startRow == row && startCol == col)
                                    possibleMoves.insert({endCol, endRow});
                            }
                        }
                    }
                    else
                    {
                        int startRow = selectedSquare.second;
                        int startCol = selectedSquare.first;
                        std::string move = gamestate.convertToMove(startRow, startCol, row, col);
                        std::set<std::string> validMoves = gamestate.getValidMoves();
                        if (validMoves.empty())
                        {
                            std::cout << "No valid moves available." << std::endl;
                        }
                        if (validMoves.count(move))
                        {
                            gamestate.makeMove(move);
                            // gamestate.displayBoard();
                        }
                        pieceSelected = false;
                        selectedSquare = {-1, -1};
                        possibleMoves.clear();
                        gamestate.getValidMoves(); // update checkmate/stalemate flags so game ends when with move that checkmates/stalemates
                        if (gamestate.checkmate)
                        {
                            std::cout << "Checkmate! Game over." << std::endl;
                        }
                        else if (gamestate.stalemate)
                        {
                            std::cout << "Stalemate! Game over." << std::endl;
                        }
                    }
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
                {
                    square.setFillColor(lightColor);
                }
                else
                {
                    square.setFillColor(darkColor);
                }
                window.draw(square);                

                // Draw pieces
                std::string piece = gamestate.board[row][col];
                sf::Sprite *sprite = nullptr;

                if (piece == "wP")
                    sprite = &whitePawn;
                else if (piece == "bP")
                    sprite = &blackPawn;
                else if (piece == "wR")
                    sprite = &whiteRook;
                else if (piece == "bR")
                    sprite = &blackRook;
                else if (piece == "wN")
                    sprite = &whiteKnight;
                else if (piece == "bN")
                    sprite = &blackKnight;
                else if (piece == "wB")
                    sprite = &whiteBishop;
                else if (piece == "bB")
                    sprite = &blackBishop;
                else if (piece == "wQ")
                    sprite = &whiteQueen;
                else if (piece == "bQ")
                    sprite = &blackQueen;
                else if (piece == "wK")
                    sprite = &whiteKing;
                else if (piece == "bK")
                    sprite = &blackKing;

                if (sprite)
                {
                    sprite->setPosition(sf::Vector2f(col * squareSize, row * squareSize));
                    window.draw(*sprite);
                }
                
                if (possibleMoves.count({col, row}))
                {
                    sf::CircleShape circle(squareSize / 5);
                    circle.setOrigin(sf::Vector2f(circle.getRadius(), circle.getRadius()));
                    circle.setPosition(sf::Vector2f(col * squareSize + squareSize / 2, row * squareSize + squareSize / 2));
                    circle.setFillColor(sf::Color(60, 60, 60, 180));
                    window.draw(circle);
                }
            }
        }
        // end the current frame
        window.display();
    }

    return 0;
}