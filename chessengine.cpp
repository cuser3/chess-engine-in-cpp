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
    whiteKingLocation = {7, 4};
    blackKingLocation = {0, 4};
    inCheck = false;
    movelog = {};

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
    int directions[4][2] = {{-1, -1}, {1, 1}, {1, -1}, {-1, 1}};

    for (auto &direction : directions)
    {
        int r = row + direction[0];
        int c = column + direction[1];

        while (r >= 0 && r <= 7 && c >= 0 && c <= 7 && board[r][c] == "--")
        {
            string move = convertToMove(row, column, r, c);
            moves.insert(move);
            r += direction[0];
            c += direction[1];
        }

        if (r >= 0 && r <= 7 && c >= 0 && c <= 7)
        {
            if ((whiteToMove && board[r][c][0] == 'b') || (!whiteToMove && board[r][c][0] == 'w'))
            {
                string move = convertToMove(row, column, r, c);
                moves.insert(move);
            }
        }
    }
}

void GameState::getAllKnightMoves(int row, int column, set<string> &moves)
{
    int knightMoves[8][2] = {{-2, -1}, {-2, 1}, {-1, 2}, {1, 2}, {2, 1}, {2, -1}, {1, -2}, {-1, -2}};

    for (auto &knightMove : knightMoves)
    {
        int r = row + knightMove[0];
        int c = column + knightMove[1];

        if (r >= 0 && r <= 7 && c >= 0 && c <= 7 && board[r][c] == "--")
        {
            string move = convertToMove(row, column, r, c);
            moves.insert(move);
        }

        if (r >= 0 && r <= 7 && c >= 0 && c <= 7)
        {
            if ((whiteToMove && board[r][c][0] == 'b') || (!whiteToMove && board[r][c][0] == 'w'))
            {
                string move = convertToMove(row, column, r, c);
                moves.insert(move);
            }
        }
    }
}

void GameState::getAllRookMoves(int row, int column, set<string> &moves)
{
    int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

    for (auto &direction : directions)
    {
        int r = row + direction[0];
        int c = column + direction[1];

        while (r >= 0 && r <= 7 && c >= 0 && c <= 7 && board[r][c] == "--")
        {
            string move = convertToMove(row, column, r, c);
            moves.insert(move);
            r += direction[0];
            c += direction[1];
        }

        if (r >= 0 && r <= 7 && c >= 0 && c <= 7)
        {
            if ((whiteToMove && board[r][c][0] == 'b') || (!whiteToMove && board[r][c][0] == 'w'))
            {
                string move = convertToMove(row, column, r, c);
                moves.insert(move);
            }
        }
    }
}

void GameState::getAllQueenMoves(int row, int column, set<string> &moves)
{
    getAllRookMoves(row, column, moves);
    getAllBishopMoves(row, column, moves);
}

void GameState::getAllKingMoves(int row, int column, set<string> &moves)
{
    int kingMoves[8][2] = {{-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}};

    for (auto &kingMove : kingMoves)
    {
        int r = row + kingMove[0];
        int c = column + kingMove[1];

        if (r >= 0 && r <= 7 && c >= 0 && c <= 7 && board[r][c] == "--")
        {
            string move = convertToMove(row, column, r, c);
            moves.insert(move);
        }

        if (r >= 0 && r <= 7 && c >= 0 && c <= 7)
        {
            if ((whiteToMove && board[r][c][0] == 'b') || (!whiteToMove && board[r][c][0] == 'w'))
            {
                string move = convertToMove(row, column, r, c);
                moves.insert(move);
            }
        }
    }
}

void GameState::checkForPinsAndChecks()
{
    vector<array<int, 4>> pins = {};
    vector<array<int, 4>> checks = {};
    bool inCheck = false;
    char enemyColor;
    char allyColor;
    int startRow;
    int startCol;
    int directions[8][2] = {{0, 1},
                            {-1, 0},
                            {1, 0},
                            {0, -1},
                            {-1, 1},
                            {-1, -1},
                            {1, 1},
                            {1, -1}};

    if (whiteToMove)
    {
        enemyColor = 'b';
        allyColor = 'w';
        startRow = this->whiteKingLocation[0];
        startCol = this->whiteKingLocation[1];
    }
    else
    {
        enemyColor = 'w';
        allyColor = 'b';
        startRow = this->blackKingLocation[0];
        startCol = this->blackKingLocation[1];
    }

    for (int j = 0; j < 8; j++)
    {
        int dir[2] = {};
        dir[0] = directions[j][0];
        dir[1] = directions[j][1];
        array<int, 4> possiblePins = {};
        for (int i = 1; i < 8; i++)
        {
            int endRow = startRow + dir[0] * i;
            int endCol = startCol + dir[1] * i;
            if (endRow >= 0 && endRow <= 7 && endCol >= 0 && endCol <= 7)
            {
                string endPiece = board[endRow][endCol];
                if (endPiece[0] == allyColor)
                {
                    if (possiblePins.empty())
                    {
                        possiblePins = {startRow, startCol, dir[0], dir[1]};
                    }
                    else
                    {
                        break;
                    }
                }
                else if (endPiece[0] == enemyColor)
                {
                    char type = endPiece[1];
                    if ((0 <= j && j <= 3 && type == 'R') ||
                        (j >= 4 && j <= 7 && type == 'B') ||
                        type == 'Q' ||
                        (i == 1 && type == 'K') ||
                        (i == 1 && type == 'P' && ((enemyColor == 'w' && j >= 6 && j <= 7) || (enemyColor == 'b' && j >= 4 && j <= 5))))
                    {
                        if (possiblePins.empty())
                        {
                            inCheck = true;
                            checks.push_back({endRow, endCol, dir[0], dir[1]});
                            break;
                        }
                        else
                        {
                            pins.push_back(possiblePins);
                            break;
                        }
                    }
                    else
                    {
                        break;
                    }
                }
            }
        }
    }
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
