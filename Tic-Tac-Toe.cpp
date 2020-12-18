#include <iostream>

using namespace std;

// forward declaration
void displayBoard(char board[3][3]);
void playerTurn(char(&board)[3][3], char player);
void computerTurn(char(&board)[3][3], char computer);
char gameOutcome(char board[3][3]);
char gameLoop(char(&board)[3][3], char player, char computer);

int main()
{
    char board[3][3] = { {' ',' ',' '}, {' ',' ',' '}, {' ',' ',' '} };
    string playerStr;

    // description of program
    cout << "Welcome to Tic-Tac-Toe! Enter whether you want to be X or O. X will go first." << endl;

    // select player's piece
    while (true)
    {
        cout << "I want to be: ";
        cin >> playerStr;
        // ensure valid input
        if (playerStr != "X" && playerStr != "O")
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
    char player = playerStr[0];

    // set computer's piece
    char computer;
    if (player == 'X')
    {
        computer = 'O';
    }
    else
    {
        computer = 'X';
    }

    // game loop
    displayBoard(board);
    char winner = gameLoop(board, player, computer);

    // state winner of game, or if game is a tie
    if (winner == '-')
    {
        cout << "Tie game!" << endl;
    }
    else
    {
        cout << winner << " wins!" << endl;
    }
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

// computer's turn
void computerTurn(char(&board)[3][3], char computer)
{
    int row;
    int column;

    cout << computer << "'s turn" << endl;
    while (true)
    {
        // input row number of piece
        while (true)
        {
            cout << "Enter the number of the row you would like to place an " << computer << " in: ";
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
            cout << "Enter the number of the column you would like to place an " << computer << " in: ";
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
    board[row - 1][column - 1] = computer;
}

// determine whether game has ended and if there is a winner
char gameOutcome(char board[3][3])
{
    // check rows for a winner
    for (int i = 0; i < 3; i++)
    {
        if (board[i][0] != ' ' && board[i][0] == board[i][1] && board[i][1] == board[i][2])
        {
            return board[i][0];
        }
    }

    // check columns for a winner
    for (int i = 0; i < 3; i++)
    {
        if (board[0][i] != ' ' && board[0][i] == board[1][i] && board[1][i] == board[2][i])
        {
            return board[0][i];
        }
    }

    // check diagonals for a winner
    if ((board[0][0] != ' ' && board[0][0] == board[1][1] && board[1][1] == board[2][2]) ||
        (board[0][2] != ' ' && board[0][2] == board[1][1] && board[1][1] == board[2][0]))
    {
        return board[1][1];
    }

    // check for tie game
    bool tieGame = true;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            tieGame = tieGame && board[i][j] != ' ';
        }
    }

    if (tieGame)
    {
        return '-';
    }
    else
    {
        return ' ';
    }
}

// main game loop
char gameLoop(char(&board)[3][3], char player, char computer)
{
    char outcome = ' ';
    // if player is X
    if (player == 'X')
    {
        while (outcome == ' ')
        {
            // player's turn
            playerTurn(board, player);
            displayBoard(board);
            // check if game has ended
            outcome = gameOutcome(board);
            if (outcome != ' ')
            {
                return outcome;
            }

            // computer's turn
            computerTurn(board, computer);
            displayBoard(board);
            // check if game has ended
            outcome = gameOutcome(board);
        }
        return outcome;
    }
    // if player is O
    else if (player == 'O')
    {
        while (outcome == ' ')
        {
            // computer's turn
            computerTurn(board, computer);
            displayBoard(board);
            // check if game has ended
            outcome = gameOutcome(board);
            if (outcome != ' ')
            {
                return outcome;
            }

            // player's turn
            playerTurn(board, player);
            displayBoard(board);
            // check if game has ended
            outcome = gameOutcome(board);
        }
        return outcome;
    }
}
