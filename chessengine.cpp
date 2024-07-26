#include <iostream>
#include <string>
#include "chessengine.h"

using namespace std;

// Constructor
GameState::GameState()
{
    whiteToMove = true;
    string initialBoard[8][8] = {
        {"bR", "bN", "bB", "bQ", "bK", "bB", "bN", "bR"},
        {"bP", "bP", "bP", "bP", "bP", "bP", "bP", "bP"},
        {"--", "--", "--", "--", "--", "--", "--", "--"},
        {"--", "--", "--", "--", "--", "--", "--", "--"},
        {"--", "--", "--", "--", "--", "--", "--", "--"},
        {"--", "--", "--", "--", "--", "--", "--", "--"},
        {"wP", "wP", "wP", "wP", "wP", "wP", "wP", "wP"},
        {"wR", "wN", "wB", "wQ", "wK", "wB", "wN", "wR"}};

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            board[i][j] = initialBoard[i][j];
        }
    }
}


void GameState::displayBoard()
{
    cout << "  a b c d e f g h" << endl;
    for (int i = 0; i < 8; i++)
    {
        cout << 8 - i << " ";
        for (int j = 0; j < 8; j++)
        {
            cout << board[i][j] << " ";
        }
        cout << 8 - i << endl;
    }
    cout << "  a b c d e f g h" << endl;
}

bool GameState::isValidMove(string move)
{
    if (move.length() != 4)
    {
        return false;
    }
    int startCol = move[0] - 'a';
    int startRow = 8 - (move[1] - '0');
    int endCol = move[2] - 'a';
    int endRow = 8 - (move[3] - '0');

    if (startCol < 0 || startCol >= 8 || endCol < 0 || endCol >= 8 || startRow < 0 || startRow >= 8 || endRow < 0 || endRow >= 8)
    {
        return false;
    }

    if (board[startRow][startCol] == "--")
    {
        return false;
    }

    return true;
}

void GameState::makeMove(string move)
{
    int startCol = move[0] - 'a';
    int startRow = 8 - (move[1] - '0');
    int endCol = move[2] - 'a';
    int endRow = 8 - (move[3] - '0');

    board[endRow][endCol] = board[startRow][startCol];
    board[startRow][startCol] = "--";
}
