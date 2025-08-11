#ifndef CHESSENGINE_H
#define CHESSENGINE_H

#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <array>

using namespace std;

class GameState
{
public:
    bool whiteToMove;
    string board[8][8];
    vector<string> movelog;
    array<int, 2> whiteKingLocation;
    array<int, 2> blackKingLocation;
    bool inCheck;
    vector<array<int, 4>> pins;
    vector<array<int, 4>> checks;
    bool checkmate;
    bool stalemate;
    array<int, 4> possibleEnPassentField;

    // Constructor
    GameState();

    // Member function to display the board
    void displayBoard();

    set<string> getValidMoves();

    void makeMove(string);

    set<string> generatePossibleMoves();

    void getAllPawnMoves(int, int, set<string> &);

    void getAllBishopMoves(int, int, set<string> &);

    void getAllKnightMoves(int, int, set<string> &);

    void getAllRookMoves(int, int, set<string> &);

    void getAllQueenMoves(int, int, set<string> &);

    void getAllKingMoves(int, int, set<string> &);

    void checkForPinsAndChecks();

    string getPromotionPiecefromUser();

    string convertToMove(int, int, int, int);
};

#endif // CHESSENGINE_H
