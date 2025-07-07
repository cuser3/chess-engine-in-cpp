#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <algorithm>
#include <array>
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
    checks = {};
    pins = {};
    checkmate = false;
    stalemate = false;

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

set<string> GameState::getValidMoves()
{
    set<string> moves = {};
    int kingRow;
    int kingCol;
    checkForPinsAndChecks();
    if (whiteToMove)
    {
        kingRow = whiteKingLocation[0];
        kingCol = whiteKingLocation[1];
    }
    else
    {
        kingRow = blackKingLocation[0];
        kingCol = blackKingLocation[1];
    }
    if (this->inCheck)
    {
        if (this->checks.size() == 1) // if King is checked by only one piece, either block the check or capture the piece
        {
            moves = generatePossibleMoves();
            array<int, 4> check = checks[0];
            int checkRow = check[0];
            int checkCol = check[1];
            string pieceChecking = board[checkRow][checkCol];
            vector<array<int, 2>> validSquares = {};
            if (pieceChecking[1] == 'N') // If Knight checks, has to be captured or King must move
            {
                validSquares.push_back({checkRow, checkCol});
            }
            else
            {
                for (int i = 0; i < 8; i++)
                {
                    array<int, 2> validSquare = {kingRow + check[2] * i, kingCol + check[3] * i}; // check[2] and check[3] are direction vectors
                    validSquares.push_back(validSquare);
                    if (validSquare[0] == checkRow && validSquare[1] == checkCol) // Break when checking piece is reached
                    {
                        break;
                    }
                }
            }
            // get rid of all moves that don't block the check or move King
            for (auto it = moves.begin(); it != moves.end();)
            {
                string move = *it;
                int startCol = move[0] - 'a';
                int startRow = 8 - (move[1] - '0');
                int endCol = move[2] - 'a';
                int endRow = 8 - (move[3] - '0');
                string movedPiece = board[startRow][startCol];
                if (movedPiece[1] != 'K') // move doesn't move King so it must be block or capture move
                {
                    array<int, 2> item = {endRow, endCol};
                    if (std::find(validSquares.begin(), validSquares.end(), item) == validSquares.end())
                    { // move doesn't block check or capture
                        it = moves.erase(it);
                        continue;
                    }
                }
                ++it;
            }
        }
        else
        {
            getAllKingMoves(kingRow, kingCol, moves); // If double check, King has to move
        }
    }
    else
    {
        moves = generatePossibleMoves(); // King not in check, so all moves are valid
    }
    if (moves.empty())
    {
        if(this->inCheck)
        {
            this->checkmate = true;
        }
        else
        {
            this->stalemate = true; 
        }
    } else {
        this->checkmate = false;
        this->stalemate = false;
    }
    return moves;
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
    bool piecePinned = false;
    std::array<int, 2> pinDirection = {0, 0};
    for (int i = static_cast<int>(this->pins.size()) - 1; i >= 0; i--)
    {
        if (this->pins[i][0] == row && this->pins[i][1] == column)
        {
            piecePinned = true;
            pinDirection[0] = this->pins[i][2];
            pinDirection[1] = this->pins[i][3];
            this->pins.erase(this->pins.begin() + i);
            break;
        }
    }

    if (whiteToMove)
    {
        if (board[row - 1][column] == "--")
        {
            if (!piecePinned || (pinDirection[0] == -1 && pinDirection[1] == 0))
            {
                string move = convertToMove(row, column, row - 1, column);
                moves.insert(move);
                if ((row == 6) && (board[row - 2][column] == "--"))
                {
                    move = convertToMove(row, column, row - 2, column);
                    moves.insert(move);
                }
            }
        }
        // captures
        if (column - 1 >= 0)
        {
            if (board[row - 1][column - 1][0] == 'b')
            {
                if (!piecePinned || (pinDirection[0] == -1 && pinDirection[1] == -1))
                {
                    string move = convertToMove(row, column, row - 1, column - 1);
                    moves.insert(move);
                }
            }
            if (column + 1 <= 7)
            {
                if (board[row - 1][column + 1][0] == 'b')
                {
                    if (!piecePinned || (pinDirection[0] == -1 && pinDirection[1] == 1))
                    {
                        string move = convertToMove(row, column, row - 1, column + 1);
                        moves.insert(move);
                    }
                }
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
                if (!piecePinned || (pinDirection[0] == 2 && pinDirection[1] == 0))
                {
                    move = convertToMove(row, column, row + 2, column);
                    moves.insert(move);
                }
            }
        }
        if (column - 1 >= 0)
        {
            if (board[row + 1][column - 1][0] == 'w')
            {
                if (!piecePinned || (pinDirection[0] == 1 && pinDirection[1] == -1))
                {
                    string move = convertToMove(row, column, row + 1, column - 1);
                    moves.insert(move);
                }
            }
        }
        if (column + 1 <= 7)
        {
            if (board[row + 1][column + 1][0] == 'w')
            {
                if (!piecePinned || (pinDirection[0] == 1 && pinDirection[1] == 1))
                {
                    string move = convertToMove(row, column, row + 1, column + 1);
                    moves.insert(move);
                }
            }
        }
    }
}

void GameState::getAllBishopMoves(int row, int column, set<string> &moves)
{
    bool piecePinned = false;
    std::array<int, 2> pinDirection = {0, 0};
    for (int i = static_cast<int>(this->pins.size()) - 1; i >= 0; i--)
    {
        if (this->pins[i][0] == row && this->pins[i][1] == column)
        {
            piecePinned = true;
            pinDirection[0] = this->pins[i][2];
            pinDirection[1] = this->pins[i][3];
            this->pins.erase(this->pins.begin() + i);
            break;
        }
    }

    int directions[4][2] = {{-1, -1}, {1, 1}, {1, -1}, {-1, 1}};

    for (auto &direction : directions)
    {
        int r = row + direction[0];
        int c = column + direction[1];

        while (r >= 0 && r <= 7 && c >= 0 && c <= 7 && board[r][c] == "--")
        {
            if (!piecePinned || (pinDirection[0] == direction[0] && pinDirection[1] == direction[1]) || (pinDirection[0] == -direction[0] && pinDirection[1] == -direction[1]))
            {
                string move = convertToMove(row, column, r, c);
                moves.insert(move);
            }
            r += direction[0];
            c += direction[1];
        }

        if (r >= 0 && r <= 7 && c >= 0 && c <= 7)
        {
            if ((whiteToMove && board[r][c][0] == 'b') || (!whiteToMove && board[r][c][0] == 'w'))
            {
                if (!piecePinned || (pinDirection[0] == direction[0] && pinDirection[1] == direction[1]) || (pinDirection[0] == -direction[0] && pinDirection[1] == -direction[1]))
                {
                    string move = convertToMove(row, column, r, c);
                    moves.insert(move);
                }
            }
        }
    }
}

void GameState::getAllKnightMoves(int row, int column, set<string> &moves)
{
    bool piecePinned = false;
    for (int i = static_cast<int>(this->pins.size()) - 1; i >= 0; i--)
    {
        if (this->pins[i][0] == row && this->pins[i][1] == column)
        {
            piecePinned = true;
            this->pins.erase(this->pins.begin() + i);
            break;
        }
    }

    int knightMoves[8][2] = {{-2, -1}, {-2, 1}, {-1, 2}, {1, 2}, {2, 1}, {2, -1}, {1, -2}, {-1, -2}};

    for (auto &knightMove : knightMoves)
    {
        int r = row + knightMove[0];
        int c = column + knightMove[1];

        if (r >= 0 && r <= 7 && c >= 0 && c <= 7 && board[r][c] == "--")
        {
            if (!piecePinned)
            {
                string move = convertToMove(row, column, r, c);
                moves.insert(move);
            }
        }

        if (r >= 0 && r <= 7 && c >= 0 && c <= 7)
        {
            if ((whiteToMove && board[r][c][0] == 'b') || (!whiteToMove && board[r][c][0] == 'w'))
            {
                if (!piecePinned)
                {
                    string move = convertToMove(row, column, r, c);
                    moves.insert(move);
                }
            }
        }
    }
}

void GameState::getAllRookMoves(int row, int column, set<string> &moves)
{
    bool piecePinned = false;
    std::array<int, 2> pinDirection = {0, 0};
    for (int i = static_cast<int>(this->pins.size()) - 1; i >= 0; i--)
    {
        if (this->pins[i][0] == row && this->pins[i][1] == column)
        {
            piecePinned = true;
            pinDirection[0] = this->pins[i][2];
            pinDirection[1] = this->pins[i][3];
            if (board[row][column][1] != 'Q')
            { // don't remove Queen from pin on Rook moves, only on Bishop moves
                this->pins.erase(this->pins.begin() + i);
            }
            break;
        }
    }

    int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

    for (auto &direction : directions)
    {
        int r = row + direction[0];
        int c = column + direction[1];

        while (r >= 0 && r <= 7 && c >= 0 && c <= 7 && board[r][c] == "--")
        {
            if (!piecePinned || (pinDirection[0] == direction[0] && pinDirection[1] == direction[1]) || (pinDirection[0] == -direction[0] && pinDirection[1] == -direction[1]))
            {
                string move = convertToMove(row, column, r, c);
                moves.insert(move);
            }
            r += direction[0];
            c += direction[1];
        }

        if (r >= 0 && r <= 7 && c >= 0 && c <= 7)
        {
            if ((whiteToMove && board[r][c][0] == 'b') || (!whiteToMove && board[r][c][0] == 'w'))
            {
                if (!piecePinned || (pinDirection[0] == direction[0] && pinDirection[1] == direction[1]) || (pinDirection[0] == -direction[0] && pinDirection[1] == -direction[1]))
                {
                    string move = convertToMove(row, column, r, c);
                    moves.insert(move);
                }
            }
        }
    }
}

void GameState::getAllQueenMoves(int row, int column, set<string> &moves)
{
    getAllRookMoves(row, column, moves);
    getAllBishopMoves(row, column, moves);
}


// TODO: maybe find more efficient way
void GameState::getAllKingMoves(int row, int column, set<string> &moves)
{
    int kingMoves[8][2] = {{-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}};

    for (auto &kingMove : kingMoves)
    {
        int r = row + kingMove[0];
        int c = column + kingMove[1];
        if (whiteToMove)
        {
            this->whiteKingLocation[0] = r;
            this->whiteKingLocation[1] = c;
        }
        else
        {
            this->blackKingLocation[0] = r;
            this->blackKingLocation[1] = c;
        }
        checkForPinsAndChecks();

        if (r >= 0 && r <= 7 && c >= 0 && c <= 7 && board[r][c] == "--")
        {
            if (!this->inCheck)
            {
                string move = convertToMove(row, column, r, c);
                moves.insert(move);
            }
        }

        if (r >= 0 && r <= 7 && c >= 0 && c <= 7)
        {
            if ((whiteToMove && board[r][c][0] == 'b') || (!whiteToMove && board[r][c][0] == 'w'))
            {
                if (!this->inCheck)
                {
                    string move = convertToMove(row, column, r, c);
                    moves.insert(move);
                }
            }
        }
        if (whiteToMove)
        {
            this->whiteKingLocation[0] = row;
            this->whiteKingLocation[1] = column;
        }
        else
        {
            this->blackKingLocation[0] = row;
            this->blackKingLocation[1] = column;
        }
    }
    checkForPinsAndChecks();
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
    int directions[8][2] = {{0, 1}, // rook moves
                            {-1, 0},
                            {1, 0},
                            {0, -1},
                            {-1, 1}, // bishop moves
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
        array<int, 4> possiblePin = {-1, -1, 0, 0};
        for (int i = 1; i < 8; i++)
        {
            int endRow = startRow + dir[0] * i;
            int endCol = startCol + dir[1] * i;
            if (endRow >= 0 && endRow <= 7 && endCol >= 0 && endCol <= 7)
            {
                string endPiece = board[endRow][endCol];
                if (endPiece[0] == allyColor && endPiece[1] != 'K')
                {
                    if (possiblePin == array<int, 4>{-1, -1, 0, 0})
                    {
                        possiblePin = {endRow, endCol, dir[0], dir[1]};
                    }
                    else
                    {
                        break; // second ally piece, so no pin possible
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
                        if (possiblePin == array<int, 4>{-1, -1, 0, 0}) // no piece blocking, so check
                        {
                            inCheck = true;
                            checks.push_back({endRow, endCol, dir[0], dir[1]});
                            break;
                        }
                        else
                        {
                            pins.push_back(possiblePin);
                            break;
                        }
                    }
                    else
                    {
                        break; // enemy piece not applying check
                    }
                }
            }
            else
            {
                break; // off the board
            }
        }
    }
    // check for knight checks
    int knightMoves[8][2] = {{-2, -1}, {-2, 1}, {-1, 2}, {1, 2}, {2, 1}, {2, -1}, {1, -2}, {-1, -2}};
    for (auto &move : knightMoves)
    {
        int endRow = startRow + move[0];
        int endCol = startCol + move[1];
        if (0 <= endRow && endRow <= 7 && 0 <= endCol && endCol <= 7)
        {
            string endPiece = board[endRow][endCol];
            if (endPiece[0] == enemyColor && endPiece[1] == 'N')
            {
                inCheck = true;
                checks.push_back({endRow, endCol, move[0], move[1]});
            }
        }
    }

    this->inCheck = inCheck;
    this->checks = checks;
    this->pins = pins;
}

void GameState::makeMove(string move)
{
    int startCol = move[0] - 'a';
    int startRow = 8 - (move[1] - '0');
    int endCol = move[2] - 'a';
    int endRow = 8 - (move[3] - '0');

    char pieceMoved = board[startRow][startCol][1];
    char color = board[startRow][startCol][0];

    if (pieceMoved == 'K')
    {
        if (color == 'w')
        {
            this->whiteKingLocation = {endRow, endCol};
        }
        else
        {
            this->blackKingLocation = {endRow, endCol};
        }
    }
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
