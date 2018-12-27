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

/**		gs_player_one_move,
		gs_player_two_move,
		gs_player_one_arrow,
		gs_player_two_arrow,
		gs_player_one_win,
		gs_player_two_win,
*/
		gs_player_move,
		gs_player_arrow,
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

	game_response play();
	game_response fire_arrow(int x, int y);
	game_response move(direction adirection);

	// The activePlayer variable takes advantage of the fact that these are reference objects
	// and can alternate between being player 1 and player 2

private:



	game_state m_state;

	const int m_height;
	const int m_width;

	std::vector< std::vector<char >> m_board;

	Player *activePlayer;
	Player playerOne;
	Player playerTwo;

	bool check_has_valid_move(Player &p);
	bool attempt_move(Player &p, direction adirection);
	bool attempt_arrow(Player &p, int x, int y);


};

}