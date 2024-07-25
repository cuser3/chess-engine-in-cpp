#include <iostream>
#include <string>

using namespace std;

void displayBoard(char board[8][8])
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

void initializeBoard(char board[8][8])
{
    // Initialize the board with spaces
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            board[i][j] = '.';
        }
    }

    // Place the pawns
    for (int i = 0; i < 8; i++)
    {
        board[1][i] = 'P'; // White pawns
        board[6][i] = 'p'; // Black pawns
    }

    // Place the rooks
    board[0][0] = board[0][7] = 'R'; // White rooks
    board[7][0] = board[7][7] = 'r'; // Black rooks

    // Place the knights
    board[0][1] = board[0][6] = 'N'; // White knights
    board[7][1] = board[7][6] = 'n'; // Black knights

    // Place the bishops
    board[0][2] = board[0][5] = 'B'; // White bishops
    board[7][2] = board[7][5] = 'b'; // Black bishops

    // Place the queens
    board[0][3] = 'Q'; // White queen
    board[7][3] = 'q'; // Black queen

    // Place the kings
    board[0][4] = 'K'; // White king
    board[7][4] = 'k'; // Black king
}

void makeMove(string move, char board[8][8])
{
    int startCol = move[0] - 'a';
    int startRow = 8 - (move[1] - '0');
    int endCol = move[2] - 'a';
    int endRow = 8 - (move[3] - '0');

    board[endRow][endCol] = board[startRow][startCol];
    board[startRow][startCol] = '.';
}

bool isValidMove(string move, char board[8][8])
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

    if (board[startRow][startCol] == '.')
    {
        return false;
    }

    return true;
}

int main()
{
    char board[8][8];

    initializeBoard(board);

    string move;

    while (true)
    {
        displayBoard(board);
        cout << "Enter your move (e.g., e2e4) or 'q' to quit: ";
        cin >> move;

        if (move == "q")
        {
            break;
        }

        if (isValidMove(move, board))
        {
            makeMove(move, board);
        }
        else
        {
            cout << "Invalid move. Please try again." << endl;
        }
    }
    return 0;
}