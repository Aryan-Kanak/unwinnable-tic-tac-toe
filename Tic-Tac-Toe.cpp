// This code was written by Aryan Kanak

#include <iostream>
#include <vector>

using namespace std;

// forward declaration
void displayBoard(char board[3][3]);
void playerTurn(char(&board)[3][3], char player);
void computerTurn(char(&board)[3][3], char computer, char player);
vector <int> findBestMove(char board[3][3], char computer, char player);
vector <vector <int>> findPossibleMoves(char board[3][3]);
int evaluateBoard(char board[3][3], char computer, char player, bool isComputerTurn);
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
void computerTurn(char(&board)[3][3], char computer, char player)
{
	// find best move
	vector <int> bestMove = findBestMove(board, computer, player);

	// update board
	board[bestMove[0]][bestMove[1]] = computer;
}

// determine best move
vector <int> findBestMove(char board[3][3], char computer, char player)
{
	// find all possible moves
	vector <vector <int>> possibleMoves = findPossibleMoves(board);

	// determine the best move
	vector <int> bestMove = possibleMoves[0];
	board[possibleMoves[0][0]][possibleMoves[0][1]] = computer;
	int bestMoveEval = evaluateBoard(board, computer, player, false);
	board[possibleMoves[0][0]][possibleMoves[0][1]] = ' ';

	int currMoveEval;
	for (int i = 1; i < possibleMoves.size(); i++)
	{
		board[possibleMoves[i][0]][possibleMoves[i][1]] = computer;
		currMoveEval = evaluateBoard(board, computer, player, false);
		if (currMoveEval > bestMoveEval)
		{
			bestMove = possibleMoves[i];
			bestMoveEval = currMoveEval;
		}
		board[possibleMoves[i][0]][possibleMoves[i][1]] = ' ';
	}

	return bestMove;
}

// find all possible moves
vector <vector <int>> findPossibleMoves(char board[3][3])
{
	vector <vector <int>> possibleMoves;
	vector <int> possibleMove;

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (board[i][j] == ' ')
			{
				possibleMove.assign({ i, j });
				possibleMoves.push_back(possibleMove);
			}
		}
	}

	return possibleMoves;
}

// evaluate state of the board
int evaluateBoard(char board[3][3], char computer, char player, bool isComputerTurn)
{
	char outcome = gameOutcome(board);
	// if computer has won
	if (outcome == computer)
	{
		return 1;
	}
	// if player has won
	else if (outcome == player)
	{
		return -1;
	}
	// if game has tied
	else if (outcome == '-')
	{
		return 0;
	}
	// if game has not ended
	else if (outcome == ' ')
	{
		vector <vector <int>> possibleMoves = findPossibleMoves(board);
		int bestEval;

		// evaluate all possible moves and find the best one
		// if it is the computer's turn
		if (isComputerTurn)
		{
			board[possibleMoves[0][0]][possibleMoves[0][1]] = computer;
			bestEval = evaluateBoard(board, computer, player, !isComputerTurn);
			board[possibleMoves[0][0]][possibleMoves[0][1]] = ' ';
			for (int i = 0; i < possibleMoves.size(); i++)
			{
				board[possibleMoves[i][0]][possibleMoves[i][1]] = computer;
				bestEval = max(bestEval, evaluateBoard(board, computer, player, !isComputerTurn));
				board[possibleMoves[i][0]][possibleMoves[i][1]] = ' ';
			}
		}
		// if it is the player's turn
		else
		{
			board[possibleMoves[0][0]][possibleMoves[0][1]] = player;
			bestEval = evaluateBoard(board, computer, player, !isComputerTurn);
			board[possibleMoves[0][0]][possibleMoves[0][1]] = ' ';
			for (int i = 0; i < possibleMoves.size(); i++)
			{
				board[possibleMoves[i][0]][possibleMoves[i][1]] = player;
				bestEval = min(bestEval, evaluateBoard(board, computer, player, !isComputerTurn));
				board[possibleMoves[i][0]][possibleMoves[i][1]] = ' ';
			}
		}

		return bestEval;
	}
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
			computerTurn(board, computer, player);
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
			computerTurn(board, computer, player);
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
