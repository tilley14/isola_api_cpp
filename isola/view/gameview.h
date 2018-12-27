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








/// Attempt move

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