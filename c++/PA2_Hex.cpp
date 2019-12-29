//============================================================================
// Name        : PA2_Hex.cpp
// Author      : michal kozinski
// Version     :
// Copyright   :
// Description : HEX Board
//============================================================================

#include <iostream>
using namespace std;
#include "Game.h"

int main() {
	Game Game1;
	Game1.Setup();
	Game1.PlayerColor();
	Game1.printBoard();
	bool gameon =1;
	while(gameon){
		Game1.PlayerTurn();
		gameon = Game1.CheckWin(false);
		if(!gameon){continue;}
		Game1.ComputerTurn();
		gameon = Game1.CheckWin(true);
		if(!gameon){continue;}
		Game1.printBoard();

	}

	Game1.printBoard();
	cout<<"Game ended!"<<endl;

	return 0;
}
