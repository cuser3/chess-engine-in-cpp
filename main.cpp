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
                    std::cout << "Left Mouse Button Pressed" << std::endl;
                    std::cout << "mouse x: " << mouseButtonpressed->position.x << std::endl;
                    std::cout << "mouse y: " << mouseButtonpressed->position.y << std::endl;
                    int col = mouseButtonpressed->position.x / squareSize;
                    int row = mouseButtonpressed->position.y / squareSize;
                    std::cout << "col: " << col << ", row: " << row << std::endl;

                    if (!pieceSelected)
                    {
                        if (gamestate.board[row][col] != "--")
                        {
                            selectedSquare = {col, row};
                            pieceSelected = true;
                            std::cout << "Piece selected at: " << selectedSquare.first << ", " << selectedSquare.second << std::endl;
                            gamestate.displayBoard();
                        }
                    }
                    else
                    {
                        int startRow = selectedSquare.second;
                        int startCol = selectedSquare.first;
                        std::string move = gamestate.convertToMove(startRow, startCol, row, col);
                        std::cout << "Attempting to make move: " << move << std::endl;
                        std::set<std::string> validMoves = gamestate.getValidMoves();
                        for (auto &move : validMoves)
                        {
                            cout << "Move: " << move << " ";
                        }
                        if (validMoves.count(move))
                        {
                            gamestate.makeMove(move);
                            gamestate.displayBoard();
                            std::cout << "Move made: " << move << std::endl;
                        }
                        pieceSelected = false;
                        selectedSquare = {-1, -1};
                        std::cout << "\n Piece unselected" << endl;
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
                    square.setFillColor(lightColor);

                else
                    square.setFillColor(darkColor);
                window.draw(square);
                

                // Draw pieces
                std::string piece = gamestate.board[row][col];
                sf::Sprite *sprite = nullptr;

                if (piece == "wP") sprite = &whitePawn;
                else if (piece == "bP") sprite = &blackPawn;
                else if (piece == "wR") sprite = &whiteRook;
                else if (piece == "bR") sprite = &blackRook;
                else if (piece == "wN") sprite = &whiteKnight;
                else if (piece == "bN") sprite = &blackKnight;
                else if (piece == "wB") sprite = &whiteBishop;
                else if (piece == "bB") sprite = &blackBishop;
                else if (piece == "wQ") sprite = &whiteQueen;
                else if (piece == "bQ") sprite = &blackQueen;
                else if (piece == "wK") sprite = &whiteKing;
                else if (piece == "bK") sprite = &blackKing;

                if (sprite)
                {
                    sprite->setPosition(sf::Vector2f(col * squareSize, row * squareSize));
                    window.draw(*sprite);
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