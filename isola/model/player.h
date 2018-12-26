class Player
{
public:

	/*
		@param avatar the character to represent the player
		@param initRow the row coordinate associated with the player
		@param initColumn the column coordinate associate with the player
	*/
	Player(char avatar, int initRow, int initColumn);

	char get_avatar();
	void set_avatar(char avatar);

	int get_row();
	void set_row(int row);

	int get_column();
	void set_column(int column);

	void set_coordinates(int row, int column);

private:
	char m_avatar;
	int  m_row;
	int  m_column;

};