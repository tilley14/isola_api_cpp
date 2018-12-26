// isola.cpp : Defines the entry point for the application.
//

#include "isola.h"
#include "controller/board.h"
using namespace GameBoard;

int main()
{
	Board isola{7, 7};
	isola.play();

	return 0;
}
