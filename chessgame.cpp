#include <iostream>
#include <string>
#include "chessengine.h"

using namespace std;


int main()
{
    GameState gamestate; 

    string move;

    while (true)
    {
        gamestate.displayBoard();
        cout << "Enter your move (e.g., e2e4) or 'q' to quit: ";
        cin >> move;

        if (move == "q")
        {
            break;
        }

        if (gamestate.isValidMove(move))
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