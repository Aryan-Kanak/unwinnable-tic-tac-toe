#include <iostream>

using namespace std;

// forward declaration
void displayBoard(char board[3][3]);
void playerTurn(char(&board)[3][3], char player);

int main()
{
    char board[3][3] = { {' ',' ',' '}, {' ',' ',' '}, {' ',' ',' '} };
    string player;

    // description of program
    cout << "Welcome to Tic-Tac-Toe! Enter whether you want to be X or O. X will go first." << endl;

    // select player
    while (true)
    {
        cout << "I want to be: ";
        cin >> player;
        // ensure valid input
        if (player != "X" && player != "O")
        {
            cout << "Invalid input!" << endl;
            cin.clear();
            cin.ignore(1000, '\n');
        }
        else
        {
            break;
        }
    }

    playerTurn(board, player[0]);
    displayBoard(board);
}

// display board
void displayBoard(char board[3][3])
{
    cout << " 1 2 3" << endl;
    cout << "1" << board[0][0] << "|" << board[0][1] << "|" << board[0][2] << endl;
    cout << " -----" << endl;
    cout << "2" << board[1][0] << "|" << board[1][1] << "|" << board[1][2] << endl;
    cout << " -----" << endl;
    cout << "3" << board[2][0] << "|" << board[2][1] << "|" << board[2][2] << endl;
}

// player's turn
void playerTurn(char(&board)[3][3], char player)
{
    int row;
    int column;

    cout << player << "'s turn" << endl;
    while (true)
    {
        // input row number of piece
        while (true)
        {
            cout << "Enter the number of the row you would like to place an " << player << " in: ";
            cin >> row;
            // ensure valid input
            if (cin.fail() || row < 1 || row > 3)
            {
                cout << "Invalid row number!" << endl;
                cin.clear();
                cin.ignore(1000, '\n');
            }
            else
            {
                break;
            }
        }

        // input column number of piece
        while (true)
        {
            cout << "Enter the number of the column you would like to place an " << player << " in: ";
            cin >> column;
            // ensure valid input
            if (cin.fail() || column < 1 || column > 3)
            {
                cout << "Invalid column number!" << endl;
                cin.clear();
                cin.ignore(1000, '\n');
            }
            else
            {
                break;
            }
        }

        // ensure there is not already a piece in the inputted spot
        if (board[row - 1][column - 1] != ' ')
        {
            cout << "This spot is occupied!" << endl;
        }
        else
        {
            break;
        }
    }

    // update board
    board[row - 1][column - 1] = player;
}
