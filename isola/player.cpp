#include "player.h"


Player::Player(char avatar, int initRow, int initColumn) :
	m_avatar{avatar},
	m_row{initRow},
	m_column{initColumn}
{

}


char Player::get_avatar()
{
	return m_avatar;
}

void Player::set_avatar(char avatar)
{
	m_avatar = avatar;
}



int Player::get_row()
{
	return m_row;
}

void Player::set_row(int row)
{
	m_row = row;
}



int Player::get_column()
{
	return m_column;
}

void Player::set_column(int column)
{
	m_column = column;
}




void Player::set_coordinates(int row, int column)
{
	Player::set_row(row);
	Player::set_column(column);
}
