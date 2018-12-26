#include "player.h"

#include <stdlib.h>
#include <string>

/*
An Isola board is 7x7 array filled with free spaces ('+')
The player's ('B' & 'W') begin in the middle of their respective edge
*/
namespace GameBoard
{
	const char EMPTY_SPOT = '+';

	enum spot
	{
		spot_empty,
		spot_occupied,
		spot_dead,
	};



class Board
{
public:
	Board(); 
	~Board();

	void play();
	void display_rules();

	std::string get_board_string();
	void draw_board();

	void clear_board();
	bool check_has_valid_move(Player &p);
	void fire_arrow(Player &p);
	bool attempt_move(Player &p, int direction);
	void move(Player &p);
	
	// The activePlayer variable takes advantage of the fact that these are reference objects
	// and can alternate between being player 1 and player 2

private:

	const int height = 7;
	const int width = 7;

	char board[7][7]{};
	
	Player *activePlayer;
	Player playerOne;
	Player playerTwo;

};

}
