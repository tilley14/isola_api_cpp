#include "gamecontroller.h"
#include <iostream>

using namespace GameController;


GameController::GameController() :
	m_initialized{false},
	m_width{ width },
	m_height{ height },
	playerOne{ 'B', 0, 3 },
	playerTwo{ 'W', 6, 3 },
	activePlayer{ nullptr },
	m_board{ m_height, std::vector<char>(m_width) }
{
	Board::clear_board();
	activePlayer = &playerOne;
	// Add the player avitars to their set location
	m_board[playerOne.get_row()][playerOne.get_column()] = playerOne.get_avatar();
	m_board[playerTwo.get_row()][playerTwo.get_column()] = playerTwo.get_avatar();
}

GameController::~GameController()
{
}

/*
	Begins a game of Isola with 2 players
	The players alternate being the activePlayer until
	the active player is no longer able to move,
	thus losing the game.
*/

/*
		Each turn will consist of
		1. check_has_valid_move()
		2. Move()
		3. FireArrow()
*/

game_response GameController::play()
{
	if (m_state == gs_uninitialized)
		return game_response{rc_uninitialized, "Game not initialized."};


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

	return game_response{ rc_game_over, "game finished successfully" };
}


/*
	The Player is asked to enter a direction to move in using the number pad.
	The input is checked to make sure a valid input was given. If the input can
	be accepted then the move will be attempted.

	@param p the player who is attempting to move
*/
game_response GameController::move(direction adirection)
{
	if (m_state == gs_uninitialized)
		return game_response{ rc_uninitialized, "Game not initialized." };

	if (m_state != gs_player_move)
		return game_response{ rc_error, "Game is not ready for a move."}

	 bool valid_move = GameController::attempt_move(p, adirection)
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
bool GameController::attempt_move(Player &p, direction adirection)
{
	bool isValidMove = true;

	// We are storing these values in a different location because we don't
	// Want to change the Player's variables unless the move is valid.
	int row = p.get_row();
	int col = p.get_column();

	// How to update the player's row and column depending
	// on the direction entered
	if (adirection == d_up_left)
	{
		row--;
		col--;
	}
	else if (adirection == d_up)
	{
		row--;
	}
	else if (adirection == d_up_right)
	{
		row--;
		col++;
	}
	else if (adirection == d_left)
	{
		col--;
	}
	else if (adirection == d_right)
	{
		col++;
	}
	else if (adirection == d_down_left)
	{
		row++;
		col--;
	}
	else if (adirection == d_down)
	{
		row++;
	}
	else if (adirection == d_down_right)
	{
		row++;
		col++;
	}
	else
	{
		// gameresponse not a valid move?
		return false;
	}


	if (row < 0 || row > m_height - 1 || col < 0 || col > m_width - 1)
	{
		std::cout << "Invalid Move, please try again: ";
		isValidMove = false;
	}
	else if (m_board[row][col] == 'A')
	{
		std::cout << "That space is dead, please try again: ";
		isValidMove = false;
	}
	else if (m_board[row][col] == playerOne.get_avatar() || m_board[row][col] == playerTwo.get_avatar())
	{
		std::cout << "That space is occupied by the opponent, please try again: ";
		isValidMove = false;
	}
	else
	{
		std::cout << "Valid Move";

		// Kill the old location of the player
		m_board[p.get_row()][p.get_column()] = 'A';

		// Update the player's location variables to the new, valid coordinates
		p.set_coordinates(row, col);

		// Add the player's avitar to the new, valid location
		m_board[p.get_row()][p.get_column()] = p.get_avatar();
		isValidMove = true;
	}

	return isValidMove;
}


/*
	"Kills" a space on the game board by replacing the '+' with
	an 'A'. Players will no longer be able to move to that space.

	@param p the player who is shooting the arrow
*/
game_response GameController::fire_arrow(int row, int col)
{
	// Todo: Check state
	if (m_state != gs_player_arrow)
		return game_response{ rc_error, "Game not ready to fire an arrow" };

	bool is_valid = GameController::attempt_fire_arrow(row, col);

	if (!is_valid)
		return game_response{ rc_error, "Arrow Shot a failure" };

	return game_response{ rc_success, "Arrow shot successful" };

	// Add the arrow to the user selected location and redraw

}

bool GameController::attempt_fire_arrow(int row, int col)
{
	// Ask for coordinates to shoot the arrow until the player inputs
	// the location of a free spot
	if (row < 0 || row > m_height || col < 0 || col > m_width)
		return false;


	if (m_board[row][col] != EMPTY_SPOT)
		return false;	// That location cannont be destroyed

	m_board[row][col] = 'A';

	return true;

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

	if (row - 1 >= 0 && col - 1 >= 0 && m_board[row - 1][col - 1] == EMPTY_SPOT)
	{
		has_valid_move = true;
	}
	else if (row - 1 >= 0 && m_board[row - 1][col] == EMPTY_SPOT)
	{
		has_valid_move = true;
	}
	else if (row - 1 >= 0 && col + 1 <= 6 && m_board[row - 1][col + 1] == EMPTY_SPOT)
	{
		has_valid_move = true;
	}
	else if (col - 1 >= 0 && m_board[row][col - 1] == EMPTY_SPOT)
	{
		has_valid_move = true;
	}
	else if (col + 1 <= m_width - 1 && m_board[row][col + 1] == EMPTY_SPOT)
	{
		has_valid_move = true;
	}
	else if (row + 1 <= m_width - 1 && col - 1 >= 0 && m_board[row + 1][col - 1] == EMPTY_SPOT)
	{
		has_valid_move = true;
	}
	else if (row + 1 <= m_width - 1 && m_board[row + 1][col] == EMPTY_SPOT)
	{
		has_valid_move = true;

	}
	else if (row + 1 <= m_height - 1 && col + 1 <= m_width - 1 && m_board[row + 1][col + 1] == EMPTY_SPOT)
	{
		has_valid_move = true;
	}

	return has_valid_move;
}


/*
	Displays the rules of the game
*/
void GameController::get_rules()
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

	return rules;
}

/*
	Draws the Isola game board with the directional key
*/
void Board::draw_board()
{

	std::string str = "  0123456\n";

	for (int i = 0; i < m_height; i++)
	{

		str += std::to_string(i) + " ";

		for (int j = 0; j < m_width; j++)
		{
			str += m_board[i][j];
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

	for (int i = 0; i < m_width; i++)
	{
		for (int j = 0; j < m_height; j++)
		{
			str += m_board[i][j];
		}

		str += "\n";
	}

	return str;
}
