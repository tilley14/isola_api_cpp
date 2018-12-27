/*
	Draws the Isola game board with the directional key
*/
void gameview::draw_board()
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



int row;
int col;

std::cout << p.get_avatar() << " time to fire an arrow!" << std::endl;


// Fire Arrow
// Ask for coordinates to shoot the arrow until the player inputs
// the location of a free spot
do
{
	// Ask for a valid row value
	do
	{
		std::cout << "Please select a row: ";

		std::cin >> row;

		if (std::cin.fail() || (row < 0 || row > 6))
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
	if (m_board[row][col] != gp_empty)
	{
		std::cout << "That location cannot be destroyed." << std::endl;
	}

} while (m_board[row][col] != gp_empty);

// Add the arrow to the user selected location and redraw
m_board[row][col] = 'A';
system("CLS");
Board::draw_board();


















bool Board::player_move(game_piece player_piece, int row, int column)
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

		// Redraw the new board
		system("CLS");
		Board::draw_board();

	}

	return isValidMove;
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
bool Board::attempt_move(player &p, int direction)
{

	else if (row < 0 || row > 6 || col < 0 || col > 6)
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

	// Redraw the new board
	system("CLS");
	Board::draw_board();

	}

	return isValidMove;
}