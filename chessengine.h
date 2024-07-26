#ifndef CHESSENGINE_H
#define CHESSENGINE_H

#include <iostream>
#include <string>

using namespace std;

class GameState
{
public:
    bool whiteToMove;
    string board[8][8];

    // Constructor
    GameState();

    // Member function to display the board
    void displayBoard();
    
    bool isValidMove(string);

    void makeMove(string);
};

#endif // CHESSENGINE_H
