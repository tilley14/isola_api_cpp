#pragma once

#include "../model/player.h"
#include "../model/board.h"

#include <stdlib.h>
#include <string>


namespace GameController
{
	enum direction {
		d_up,
		d_up_left,
		d_left,
		d_down_left,
		d_down,
		d_down_right,
		d_right,
		d_up_right
	};

	enum game_state {
		gs_uninitialized,
		gs_initialized,
		gs_turn_begin,

/**		
		gs_player_one_move,
		gs_player_two_move,
		gs_player_one_arrow,
		gs_player_two_arrow,
		gs_player_one_win,
		gs_player_two_win,
*/
		gs_player_move,
		gs_player_arrow,
		gs_turn_end,
		gs_game_finished
	};

	enum response_code {
		rc_success,
		rc_error,
		rc_uninitialized,
		rc_player_one_win,
		rc_player_two_win
	};

	struct game_response
	{
		response_code code;
		std::string message;
	};

class GameController
{
public:
	GameController();
	~GameController();

	std::string get_rules();
	game_response initialize();
	game_response start_game();

	game_response begin_turn();
	game_response fire_arrow(int x, int y);
	game_response move(direction adirection);
	game_response end_turn();

	const std::vector< std::vector< GameBoard::game_piece>> get_board();


	// The activePlayer variable takes advantage of the fact that these are reference objects
	// and can alternate between being player 1 and player 2

private:

	game_state m_state;

	GameBoard::Board m_gameboard;

	GameBoard::game_piece m_active_player;
	Player playerOne;
	Player playerTwo;

	bool check_has_valid_move(GameBoard::game_piece p);
	bool attempt_move(GameBoard::game_piece p, direction adirection);

};

}