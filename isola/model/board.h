#include <stdlib.h>
#include <string>
#include <vector>
#include <map>

#include "player.h"

/*
An Isola board is 7x7 array filled with free spaces ('+')
The player's ('B' & 'W') begin in the middle of their respective edge
*/
namespace GameBoard
{
	enum game_piece
	{
		gp_empty,
		gp_player_one,
		gp_player_two,
		gp_dead
	};

	struct player {
		const game_piece piece;
		int row;
		int column;
		const int start_row;
		const int start_col;
	};

class Board
{
public:
	Board(int width, int height); 
	~Board();

	void clear_board();
	void set_players();
	void reset_board();

	bool check_has_valid_move(player &p);
	bool kill_space(int row, int column);
	bool move_player(game_piece player_piece, int row, int column);

	bool new_player(game_piece player_piece, int start_row, int start_column);
	player* get_player(game_piece player_piece);

	const std::vector< std::vector<game_piece >> get_board();

	const int m_height;
	const int m_width;
	
	// The activePlayer variable takes advantage of the fact that these are reference objects
	// and can alternate between being player 1 and player 2

private:

	std::vector< std::vector<game_piece >> m_board;
	std::map< game_piece, player> m_players;	
};

}
