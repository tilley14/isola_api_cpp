// isola.cpp : Defines the entry point for the application.
//

#include "isola.h"
#include "controller/gamecontroller.h"
using namespace GameController;

int main()
{
	GameController isola{};
	isola.play();

	return 0;
}
