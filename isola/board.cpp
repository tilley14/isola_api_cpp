#include "board.h"
#include <iostream>

using namespace GameBoard;


Board::Board() :
	playerOne{'B', 0, 3},
	playerTwo{'W', 6, 3},
	activePlayer{nullptr}
{
	Board::clear_board();
	activePlayer = &playerOne;
	// Add the player avitars to their set location
	board[playerOne.get_row()][playerOne.get_column()] = playerOne.get_avatar();
	board[playerTwo.get_row()][playerTwo.get_column()] = playerTwo.get_avatar();
}

Board::~Board()
{
}

void Board::clear_board()
{
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			board[i][j] = EMPTY_SPOT;
		}
	}
}

/*
	Begins a game of Isola with 2 players
	The players alternate being the activePlayer until
	the active player is no longer able to move,
	thus losing the game.
*/
void Board::play()
{
	Board::display_rules();
	Board::draw_board();

	/*
		Each turn will consist of
		1. check_has_valid_move()
		2. Move()
		3. FireArrow()
	*/


	// Check if the activePlayer can move.
	// If the activePlayer cannot move, the loop will end.
	while (Board::check_has_valid_move(*activePlayer))
	{
		Board::move(*activePlayer);
		Board::fire_arrow(*activePlayer);

		if (activePlayer->get_avatar() == 'B')
		{
			activePlayer = &playerTwo;
		}
		else
		{
			activePlayer = &playerOne;
		}

	}

	// If the activePlayer cannot move, the activePlayer loses the game.
	std::cout << activePlayer->get_avatar() + " is no longer able to move!" << std::endl;
	if (activePlayer->get_avatar() == 'B')
	{
		std::cout << playerTwo.get_avatar() + " is the winner" << std::endl;
	}
	else
	{
		std::cout << playerOne.get_avatar() + " is the winner" << std::endl;
	}
	
	std::cout << "Press Enter to continue" << std::endl;
	std::cin.ignore();

	while (1)
		;
}


/*
	The Player is asked to enter a direction to move in using the number pad.
	The input is checked to make sure a valid input was given. If the input can
	be accepted then the move will be attempted.

	@param p the player who is attempting to move
*/
void Board::move(Player &p)
{
	std::cout << "Turn: " << p.get_avatar() << "\nUse the number pad to move in a direction 1-9, but not 5 (see key): ";
	int direction = 0;

	bool valid = false;

	// Continue attempting to move until the move is successful
	do
	{

		// Ask for user input until a valid input has been recieved
		do
		{

			std::cin >> direction;

			if (std::cin.fail() || direction == 5 || (direction < 1 || direction > 9))
			{
				std::cin.clear();
				std::cin.ignore();
				std::cout << "Invalid Input!" << std::endl;
				std::cout << "Turn: " << p.get_avatar() << "\nUse the number pad to move in a direction 1-9, but not 5 (see key): ";

			}
			else
			{
				valid = true;
			}

		} while (!valid);

	} while (Board::attempt_move(p, direction) == false);
}


/*
	Once The user has entered a valid input, the move has to be attempted.
	The direction that the user provided is used to see what is in the new space.
	If the new space is an empty space, the method will move the player to that new space,
	update the player objects location variables, and return true that the move was successful.
	If the new space is occupied, killed, or out of bounds the move will fail and the method
	will return false.

	@param p the player that is attempting to move
	@param direction the direction in which the player is attempting to move
	@return isValidMove weather or not the move can be made
*/
bool Board::attempt_move(Player &p, int direction)
{
	bool isValidMove = true;

	// We are storing these values in a different location because we don't
	// Want to change the Player's variables unless the move is valid.
	int row = p.get_row();
	int col = p.get_column();

	// How to update the player's row and column depending
	// on the direction entered
	if (direction == 7)
	{
		row--;
		col--;
	}
	else if (direction == 8)
	{
		row--;
	}
	else if (direction == 9)
	{
		row--;
		col++;
	}
	else if (direction == 4)
	{
		col--;
	}
	else if (direction == 6)
	{
		col++;
	}
	else if (direction == 1)
	{
		row++;
		col--;
	}
	else if (direction == 2)
	{
		row++;
	}
	else if (direction == 3)
	{
		row++;
		col++;
	}

	// Error messages for invalid inputs
	if (direction == 5)
	{
		std::cout << "5 is not a direction, please try again: ";
		isValidMove = false;
	}
	else if (row < 0 || row > 6 || col < 0 || col > 6)
	{
		std::cout << "Invalid Move, please try again: ";
		isValidMove = false;
	}
	else if (board[row][col] == 'A')
	{
		std::cout << "That space is dead, please try again: ";
		isValidMove = false;
	}
	else if (board[row][col] == playerOne.get_avatar() || board[row][col] == playerTwo.get_avatar())
	{
		std::cout << "That space is occupied by the opponent, please try again: ";
		isValidMove = false;
	}
	else
	{
		std::cout << "Valid Move";

		// Kill the old location of the player
		board[p.get_row()][p.get_column()] = 'A';

		// Update the player's location variables to the new, valid coordinates
		p.set_coordinates(row, col);

		// Add the player's avitar to the new, valid location
		board[p.get_row()][p.get_column()] = p.get_avatar();
		isValidMove = true;

		// Redraw the new board
		system("CLS");
		Board::draw_board();

	}

	return isValidMove;
}


/*
	"Kills" a space on the game board by replacing the '+' with
	an 'A'. Players will no longer be able to move to that space.

	@param p the player who is shooting the arrow
*/
void Board::fire_arrow(Player &p)
{
	int row;
	int col;

	std::cout << p.get_avatar()  << " time to fire an arrow!" << std::endl;

	// Ask for coordinates to shoot the arrow until the player inputs
	// the location of a free spot
	do
	{
		// Ask for a valid row value
		do
		{
			std::cout << "Please select a row: ";

			std::cin >> row;

			if ( std::cin.fail() || (row < 0 || row > 6))
			{
				row = -1;
				std::cin.clear();
				std::cin.ignore();
				std::cout << "Invalid coordinate!" << std::endl;
			}

		} while (row < 0 || row > 6);

		// Ask for a valid column value
		do
		{
			std::cout << "Please select a column: ";


			std::cin >> col;


			if (std::cin.fail() || (col < 0 || col > 6))
			{
				col = -1;
				std::cin.clear();
				std::cin.ignore();
				std::cout << "Invalid coordinate!" << std::endl;
			}

		} while (col < 0 || col > 6);

		// Error message if the valid inputs for row and column do not 
		// Contain a free space ('+')
		if (board[row][col] != EMPTY_SPOT)
		{
			std::cout << "That location cannot be destroyed." << std::endl;
		}

	} while (board[row][col] != EMPTY_SPOT);

	// Add the arrow to the user selected location and redraw
	board[row][col] = 'A';
	system("CLS");
	Board::draw_board();
}

/*
	Looks in all 8 directions a player could possibly move and if one of those
	places contains a free space ('+'), then the player has a valid move availible
	and the method returns true. If the player cannot move, then the method returns false

	@param p the player who is being checked for a valid move
	@return has_valid_move true if there is a free space the player can move to,
		false if there is not.
*/
bool Board::check_has_valid_move(Player &p)
{
	bool has_valid_move = false;
	int row = p.get_row();
	int col = p.get_column();

	/*
		Each if statement first checks to see if the player is on an edge.
		We do not want to attempt to check a spot on a board that is out of bounds.
		If the spot is within the bounds of the board, then that spot is
		checked for a free space ('+').
	*/

	if (row - 1 >= 0 && col - 1 >= 0 && board[row - 1][col - 1] == EMPTY_SPOT)
	{
		has_valid_move = true;
	}
	else if (row - 1 >= 0 && board[row - 1][col] == EMPTY_SPOT)
	{
		has_valid_move = true;
	}
	else if (row - 1 >= 0 && col + 1 <= 6 && board[row - 1][col + 1] == EMPTY_SPOT)
	{
		has_valid_move = true;
	}
	else if (col - 1 >= 0 && board[row][col - 1] == EMPTY_SPOT)
	{
		has_valid_move = true;
	}
	else if (col + 1 <= 6 && board[row][col + 1] == EMPTY_SPOT)
	{
		has_valid_move = true;
	}
	else if (row + 1 <= 6 && col - 1 >= 0 && board[row + 1][col - 1] == EMPTY_SPOT)
	{
		has_valid_move = true;
	}
	else if (row + 1 <= 6 && board[row + 1][col] == EMPTY_SPOT)
	{
		has_valid_move = true;

	}
	else if (row + 1 <= 6 && col + 1 <= 6 && board[row + 1][col + 1] == EMPTY_SPOT)
	{
		has_valid_move = true;
	}

	return has_valid_move;
}


/*
	Displays the rules of the game
*/
void Board::display_rules()
{
	std::string rules = 
		"********** Isola Game **********"
		"\nEach player has one piece."
		"\nThe Board has 7 by 7 positions, which initially contain"
		"\nfree spaces ('+') except for the initial positions"
		"\nof the players. A Move consists of two subsequent actions:"
		"\n\n1. Moving one's piece to a neighboring (horizontally, vertically,"
		"\ndiagonally) field that contains a '+' but not the opponents piece."
		"\n\n2. Removing any '+' with no piece on it (Replacing it with an 'A')."
		"\n\nIf player cannot move at the beginning of their turn, he/she loses the game."
		"\nPress any key to start... ";

	std::cout << rules;
	std::cin.ignore();

}

/*
	Draws the Isola game board with the directional key
*/
void Board::draw_board()
{

	std::string str = "  0123456\n";

	for (int i = 0; i < height; i++)
	{

		str +=  std::to_string(i) + " ";

		for (int j = 0; j < width; j++)
		{
			str += board[i][j];
		}

		str += "\n";
	}

	str += "\n7-8-9"
		   "\n4---6"
		   "\n1-2-3";

	system("CLS");
	std::cout << str << std::endl;
}

/*
	Returns the Isola game board with nothing added
*/
std::string Board::get_board_string()
{
	std::string str = "";

	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			str += board[i][j];
		}

		str += "\n";
	}

	return str;
}
