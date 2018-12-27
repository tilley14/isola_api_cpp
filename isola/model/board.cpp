#include "board.h"
#include <iostream>
#include <math.h>

using namespace GameBoard;


Board::Board(int width, int height) :
	m_width{width},
	m_height{height},
	m_board{ m_height, std::vector<char>(m_width) }
{
	Board::clear_board();
}

Board::~Board()
{
}

void Board::clear_board()
{
	for (int r = 0; r < m_height; r++)
	{
		for (int c = 0; c < m_width; c++)
		{
			m_board[r][c] = gp_empty;
		}
	}
}

void Board::set_players()
{
	for (auto &pair : m_players)
	{
		player &p = pair.second;
		p.row = p.start_row;
		p.column = p.start_col;
		m_board[p.row][p.column] = p.piece;
	}
}

void Board::reset_board()
{
	Board::clear_board();
	Board::set_players();
}

bool Board::new_player(game_piece player_piece, int start_row, int start_column)
{
	if (player_piece == gp_empty || player_piece == gp_dead)
		return false;

	// Check to see if the game piece is already in use
	auto search = m_players.find(player_piece);

	// Player piece in use, new player failed
	if (search != m_players.end())
		return false;

	// Add the new player to the 
	m_board[player_piece] = {player_piece, start_row, start_column, start_row, start_column};

	return true;
}

player* Board::get_player(game_piece player_piece)
{
	auto search = m_players.find(player_piece);

	if (search == m_players.end())
		return nullptr;

	return &m_players[player_piece];
}

/*
	The Player is asked to enter a direction to move in using the number pad.
	The input is checked to make sure a valid input was given. If the input can
	be accepted then the move will be attempted.

	@param p the player who is attempting to move
*/
bool Board::move_player(game_piece player_piece, int row, int column)
{
	player* aplayer = Board::get_player(player_piece);

	// Fail if piece is not a player or row or column is out of range
	if (!aplayer || row < 0 || row > m_height - 1 || column < 0 || column > m_width - 1)
		return false;

	// Cannot move to a spot that is not empty
	if (m_board[row][column] != gp_empty)
		return false;

	// Can only move to adjacent spots
	if (abs(row - aplayer->row) > 1 || abs(column - aplayer->column) > 1)
		return false;
	
	// Move Piece and kill old spot
	m_board[aplayer->row][aplayer->column] = gp_empty;
	Board::kill_space(aplayer->row, aplayer->column);

	// Update player's position
	aplayer->row = row;
	aplayer->column = column;

	// Place the player's game piece back onto the board
	m_board[aplayer->row][aplayer->column] = aplayer.piece;	
	
	return true;
}


/*
	"Kills" a space on the game board by replacing the gp_empty with
	an gp_dead. Players will no longer be able to move to that space.

	@param p the player who is shooting the arrow
*/
bool Board::kill_space(int row, int column)
{
	if (row < 0 || row > m_height - 1 || column < 0 || column > m_width - 1)
		return false;

	if (m_board[row][column] != gp_empty)
		return false;

	// Kill that space
	m_board[row][column] = gp_dead;
	return true;

}

/*
	Looks in all 8 directions a player could possibly move and if one of those
	places contains a free space (gp_empty), then the player has a valid move availible
	and the method returns true. If the player cannot move, then the method returns false

	@param p the player who is being checked for a valid move
	@return has_valid_move true if there is a free space the player can move to,
		false if there is not.
*/
bool Board::check_has_valid_move(player &aplayer)
{
	for (int i = -1; i <= 1; i++)
	{
		for (int j = -1; j <= 1; i++)
		{
			check_row = aplayer.row + i;
			check_col = aplayer.column + j;
			if (check_row >= 0 && check_row < m_height && check_col >= 0 && check_col < m_width)
			{
				if (m_board[check_row][check_col] == gp_empty)
					return true;
			}
		}
	}

	return false;

	/*
		Each if statement first checks to see if the player is on an edge.
		We do not want to attempt to check a spot on a board that is out of bounds.
		If the spot is within the bounds of the board, then that spot is
		checked for a free space (gp_empty).
	*/
	/*
	bool has_valid_move = false;
	int row = aplayer.row;
	int col = aplayer.column;


	if (row - 1 >= 0 && col - 1 >= 0 && m_board[row - 1][col - 1] == gp_empty)
	{
		has_valid_move = true;
	}
	else if (row - 1 >= 0 && m_board[row - 1][col] == gp_empty)
	{
		has_valid_move = true;
	}
	else if (row - 1 >= 0 && col + 1 <= 6 && m_board[row - 1][col + 1] == gp_empty)
	{
		has_valid_move = true;
	}
	else if (col - 1 >= 0 && m_board[row][col - 1] == gp_empty)
	{
		has_valid_move = true;
	}
	else if (col + 1 <= m_width - 1  && m_board[row][col + 1] == gp_empty)
	{
		has_valid_move = true;
	}
	else if (row + 1 <= m_width - 1 && col - 1 >= 0 && m_board[row + 1][col - 1] == gp_empty)
	{
		has_valid_move = true;
	}
	else if (row + 1 <= m_width - 1 && m_board[row + 1][col] == gp_empty)
	{
		has_valid_move = true;

	}
	else if (row + 1 <= m_height - 1 && col + 1 <= m_width - 1 && m_board[row + 1][col + 1] == gp_empty)
	{
		has_valid_move = true;
	}

	return has_valid_move;

	*/
}




/*
	Returns the Isola game board with nothing added
*/
const std::vector< std::vector<game_piece >> Board::get_board()
{
	return m_board;
}
