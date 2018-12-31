#include "gamecontroller.h"
#include <iostream>

using namespace GameController;


GameController::GameController() :
	m_initialized{false},
	playerOne{ 'B', 0, 3 },
	playerTwo{ 'W', 6, 3 },
	m_active_player{ GameBoard::gp_player_one },
	m_gameboard{7, 7}
{
	// Add the player avitars to their set location
	//m_gameboard[playerOne.get_row()][playerOne.get_column()] = playerOne.get_avatar();
	//m_gameboard[playerTwo.get_row()][playerTwo.get_column()] = playerTwo.get_avatar();
}

GameController::~GameController()
{
}

game_response GameController::initialize()
{
	if (m_state != gs_uninitialized)
		return game_response{ rc_error, "Unable to initialize." };

	// Init board


	m_state = gs_initialized;
	return game_response{ rc_success, "Game Initialization Successful." };
}

game_response GameController::start_game()
{
	if(m_state != gs_initialized)
		return game_response{ rc_error, "Game not ready to start."}

	m_state = gs_turn_begin;
	return game_response{ rc_success, "Game start successful." };
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

game_response GameController::begin_turn()
{
	if (m_state == gs_uninitialized)
		return game_response{rc_uninitialized, "Game not initialized."};

	if (m_state != gs_turn_begin)
		return game_rsponse{ rc_error, "Not able to to begin turn." };




	// Check if the activePlayer can move.
	// If the activePlayer cannot move, the loop will end.
	while (GameController::check_has_valid_move(m_active_player))
	{
		//Board::move(*activePlayer);
		//Board::fire_arrow(*activePlayer);



	}

	// If the activePlayer cannot move, the activePlayer loses the game.
	// std::cout << activePlayer->get_avatar() + " is no longer able to move!" << std::endl;
	// if (activePlayer->get_avatar() == 'B')
	// {
	// 	std::cout << playerTwo.get_avatar() + " is the winner" << std::endl;
	// }
	// else
	// {
	// 	std::cout << playerOne.get_avatar() + " is the winner" << std::endl;
	// }

	// std::cout << "Press Enter to continue" << std::endl;
	// std::cin.ignore();

	return game_response{ rc_game_over, "Game finished successfully." };
}

game_response GameController::end_turn()
{
	if (m_state != gs_turn_end)
		return game_response{ rc_error, "Turn could not be completed." };

	if (m_active_player == GameBoard::gp_player_one)
	{
		m_active_player = GameBoard::gp_player_two;
	}
	else
	{
		m_active_player = GameBoard::gp_player_one;
	}

	m_state = gs_turn_begin;
	return game_response{ rc_success, "Turn ended successfully. Starting next player's turn."}

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

	// Try to kill the space
	bool is_valid = m_gameboard.kill_space(row, col);

	if (!is_valid)
		return game_response{ rc_error, "Arrow Shot a failure" };

	m_state = gs_player_move;
	return game_response{ rc_success, "Arrow shot successful" };
}

/*
	The Player is asked to enter a direction to move in using the number pad.
	The input is checked to make sure a valid input was given. If the input can
	be accepted then the move will be attempted.

	@param p the player who is attempting to move
*/
game_response GameController::move(GameBoard::game_piece p, direction adirection)
{
	if (m_state == gs_uninitialized)
		return game_response{ rc_uninitialized, "Game not initialized." };

	if (m_state != gs_player_move)
		return game_response{ rc_error, "Game is not ready for a move." };

	bool valid_move = GameController::attempt_move(p, adirection);

	if (!valid_move)
		return game_response{rc_error, "Unable to move player."};

	m_state = gs_player_arrow;
	return game_response{rc_success, "Player successfully moved."};
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
bool GameController::attempt_move(GameBoard::game_piece p, direction adirection)
{
	GameBoard::player *aplayer = m_gameboard.get_player(p);

	if (!(*aplayer))
		return false;


	// We are storing these values in a different location because we don't
	// Want to change the Player's variables unless the move is valid.
	int row = (*aplayer).get_row();
	int col = (*aplayer).get_column();

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


	return m_gameboard.move_player(p, row, col);
}


/*
	Looks in all 8 directions a player could possibly move and if one of those
	places contains a free space ('+'), then the player has a valid move availible
	and the method returns true. If the player cannot move, then the method returns false

	@param p the player who is being checked for a valid move
	@return has_valid_move true if there is a free space the player can move to,
		false if there is not.
*/
bool GameController::check_has_valid_move(GameBoard::game_piece p)
{	
	GameBoard::player *aplayer = m_gameboard.get_player(p);

	if (!(*aplayer))
		return false;

	return m_gameboard.check_has_valid_move(*aplayer);
}


/*
	Displays the rules of the game
*/
std::string GameController::get_rules()
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
	Returns the Isola game board with nothing added
*/
const std::vector< std::vector< GameBoard::game_piece>> GameController::get_board()
{
	return m_gameboard.get_board();
}
