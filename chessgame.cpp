#include <iostream>
#include <string>
#include "chessengine.h"
#include <set>

using namespace std;

int main()
{
    GameState gamestate;

    string move;

    while (true)
    {
        gamestate.displayBoard();
        set<string> validMoves = gamestate.getValidMoves();
        cout << "Enter your move (e.g., e2e4) or 'q' to quit: ";
        cin >> move;

        if (move == "q")
        {
            break;
        }

        if (validMoves.count(move))
        {
            gamestate.makeMove(move);
        }
        else
        {
            cout << "Invalid move. Please try again." << endl;
        }
    }
    return 0;
}