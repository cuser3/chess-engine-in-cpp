#include <iostream>
#include <string>
#include <vector>
#include <set>
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
    cout << "  a  b  c  d  e  f  g  h" << endl;
    for (int i = 0; i < 8; i++)
    {
        cout << 8 - i << " ";
        for (int j = 0; j < 8; j++)
        {
            cout << board[i][j] << " ";
        }
        cout << 8 - i << endl;
    }
    cout << "  a  b  c  d  e  f  g  h" << endl;
}

bool GameState::isValidMove(string move)
{
    return true;
}

set<string> GameState::generatePossibleMoves()
{
    set<string> possibleMoves;
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            char pieceColor = board[i][j][0];
            if ((pieceColor == 'w' && whiteToMove) || (pieceColor == 'b' && !whiteToMove))
            {
                char pieceType = board[i][j][1];
                switch (pieceType)
                {
                case 'P':
                    getAllPawnMoves(i, j, possibleMoves);
                    break;
                case 'B':
                    getAllBishopMoves(i, j, possibleMoves);
                    break;
                case 'N':
                    getAllKnightMoves(i, j, possibleMoves);
                    break;
                case 'R':
                    getAllRookMoves(i, j, possibleMoves);
                    break;
                case 'Q':
                    getAllQueenMoves(i, j, possibleMoves);
                    break;
                case 'K':
                    getAllKingMoves(i, j, possibleMoves);
                    break;
                }
            }
        }
    }

    return possibleMoves;
}

void GameState::getAllPawnMoves(int row, int column, set<string> &moves)
{
    if (whiteToMove)
    {
        if (board[row - 1][column] == "--")
        {
            string move = convertToMove(row, column, row - 1, column);
            moves.insert(move);
            if ((row == 6) && (board[row - 2][column] == "--"))
            {
                move = convertToMove(row, column, row - 2, column);
                moves.insert(move);
            }
        }
        if (column - 1 >= 0)
        {
            if (board[row - 1][column - 1][0] == 'b')
            {
                string move = convertToMove(row, column, row - 1, column - 1);
                moves.insert(move);
            }
        }
        if (column + 1 <= 7)
        {
            if (board[row - 1][column + 1][0] == 'b')
            {
                string move = convertToMove(row, column, row - 1, column + 1);
                moves.insert(move);
            }
        }
    }
    else
    {
        if (board[row + 1][column] == "--")
        {
            string move = convertToMove(row, column, row + 1, column);
            moves.insert(move);
            if ((row == 1) && (board[row + 2][column] == "--"))
            {
                move = convertToMove(row, column, row + 2, column);
                moves.insert(move);
            }
        }
        if (column - 1 >= 0)
        {
            if (board[row + 1][column - 1][0] == 'w')
            {
                string move = convertToMove(row, column, row + 1, column - 1);
                moves.insert(move);
            }
        }
        if (column + 1 <= 7)
        {
            if (board[row + 1][column + 1][0] == 'w')
            {
                string move = convertToMove(row, column, row + 1, column + 1);
                moves.insert(move);
            }
        }
    }
}

void GameState::getAllBishopMoves(int row, int column, set<string> &moves)
{
}

void GameState::getAllKnightMoves(int row, int column, set<string> &moves)
{
}

void GameState::getAllRookMoves(int row, int column, set<string> &moves)
{
    int r = row;
    int c = column;

    if (r - 1 >= 0) {
        while (board[r - 1][column] == "--") {
            string move = convertToMove(row, column, r - 1, column);
            moves.insert(move);
            r--;
        }
        if ((whiteToMove && board[r - 1][column][0] == 'b') || !whiteToMove && board[r - 1][column][0] == 'w') {
            string move = convertToMove(row, column, r - 1, column);
            moves.insert(move);
        }
    }
    r = row;
    if (r + 1 <= 7) {
        while (board[r + 1][column] == "--") {
            string move = convertToMove(row, column, r + 1, column);
            moves.insert(move);
            r++;
        }
        if ((whiteToMove && board[r + 1][column][0] == 'b') || !whiteToMove && board[r + 1][column][0] == 'w') {
            string move = convertToMove(row, column, r + 1, column);
            moves.insert(move);
        }
    }
    if (c - 1 >= 0) {
        while (board[row][c - 1] == "--") {
            string move = convertToMove(row, column, row, c - 1);
            moves.insert(move);
            c--;
        }
        if ((whiteToMove && board[row][c - 1][0] == 'b') || !whiteToMove && board[row][c - 1][0] == 'w') {
            string move = convertToMove(row, column, row, c - 1);
            moves.insert(move);
        }
    }
    c = column;
    if (c + 1 <= 7) {
        while (board[row][c + 1] == "--") {
            string move = convertToMove(row, column, row, c + 1);
            moves.insert(move);
            c++;
        }
        if ((whiteToMove && board[row][c + 1][0] == 'b') || !whiteToMove && board[row][c + 1][0] == 'w') {
            string move = convertToMove(row, column, row, c + 1);
            moves.insert(move);
        }
    }
}

void GameState::getAllQueenMoves(int row, int column, set<string> &moves)
{
}

void GameState::getAllKingMoves(int row, int column, set<string> &moves)
{
}

void GameState::makeMove(string move)
{
    int startCol = move[0] - 'a';
    int startRow = 8 - (move[1] - '0');
    int endCol = move[2] - 'a';
    int endRow = 8 - (move[3] - '0');

    board[endRow][endCol] = board[startRow][startCol];
    board[startRow][startCol] = "--";

    movelog.push_back(move);
    whiteToMove = !whiteToMove;
}

string GameState::convertToMove(int startRow, int startCol, int endRow, int endCol)
{
    char startColChar = 'a' + startCol;
    char endColChar = 'a' + endCol;
    int startRowNum = 8 - startRow;
    int endRowNum = 8 - endRow;

    return string(1, startColChar) + to_string(startRowNum) + string(1, endColChar) + to_string(endRowNum);
}
