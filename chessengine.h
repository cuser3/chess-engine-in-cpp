#ifndef CHESSENGINE_H
#define CHESSENGINE_H

#include <iostream>
#include <string>
#include <vector>
#include <set>

using namespace std;

class GameState
{
public:
    bool whiteToMove;
    string board[8][8];
    vector<string> movelog;

    // Constructor
    GameState();

    // Member function to display the board
    void displayBoard();
    
    bool isValidMove(string);

    void makeMove(string);

    set<string> generatePossibleMoves();

    void getAllPawnMoves(int, int, set<string> &);

    void getAllBishopMoves(int, int, set<string>);

    void getAllKnightMoves(int, int, set<string>);

    void getAllRookMoves(int, int, set<string>);

    void getAllQueenMoves(int, int, set<string>);

    void getAllKingMoves(int, int, set<string>);

    string convertToMove(int, int, int, int);
};

#endif // CHESSENGINE_H
