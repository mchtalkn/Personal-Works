/*
 * Game.h
 *
 *  Created on: Oct 12, 2019
 *      Author: michalkozinski
 */

#ifndef GAME_H_
#define GAME_H_
#include "Board.h"

class Game {
public:
	Game();
	virtual ~Game();
	void Setup();
	void PlayerColor();
	void printBoard(unsigned int round = 0);
	void PlayerTurn();
	void ComputerTurn();
	bool CheckWin(bool isAI);

private:
	Board* board1;
	int size;
	Player player;
	State playerColor;
	Player computer;
	State computerColor;
	vector<vector<int> > graphArray;

};

Game::Game() {} // @suppress("Class members should be properly initialized")
Game::~Game() {}
void Game::Setup(){
	cout<<"How big would you like?"<<endl;
	cin>>size;
	if(size >40 || size < 2){
		cout<<"Wrong board size! Setting up 12x12!"<<endl;
		size = 12;
	}

	cin.clear();
	board1 = new Board(size);
}
void Game::PlayerColor(){
	char color;
	color = 'B';

	cout<<"Choose the side: Red or Blue (R/B)."<<endl;
	cin>>color;

	cin.clear();

	if(color == 'R' || color == 'r')
	{
		player = Player::P_RED;
		playerColor = State::H_RED;
		computer = Player::P_BLUE;
		computerColor = State::H_BLUE;
	}
	else if(color == 'B' || color == 'b')
	{
		player = Player::P_BLUE;
		playerColor = State::H_BLUE;
		computer = Player::P_RED;
		computerColor = State::H_RED;
	}
	else
	{
		cout << "Wrong choice! You have been assigned color RRRRed!"<<endl;
		player = Player::P_RED;
		playerColor = State::H_RED;
		computer = Player::P_BLUE;
		computerColor = State::H_BLUE;
	}
	cout<<"Player connects horizontally, computer vertically! Good luck!"<<endl;
}
void Game::printBoard(unsigned int round){
	int sideLength = board1->getSideSize();
	/////PRINT THE TOP LINE
	for (int i = 0; i<sideLength; i++){cout<<"---------"<<flush;}
	cout<<endl<<setw(4)<<" "<<flush;
	for(int i = 0;i<sideLength;i++){cout<<setw(3)<<i<<flush;}
	cout<<endl<<setw(4)<<" "<<flush;
	for(int i = 0;i<sideLength;i++){cout<<setw(3)<<computer<<flush;}
	cout<<endl<<"";

	for(int y = 0; y<sideLength; y++){
		for(int i = 0;i<y;i++){cout<<setw(3)<<" "<<flush;}
		for(int i = 0;i<y;i++){cout<<" "<<flush;}
		cout<<setw(3)<<y<<" "<<player<<flush;
		for (int x = 0; x<sideLength; x++){
			cout<<setw(3)<<board1->HexState(x,y)<<flush;
		}
		cout<<setw(3)<<player;
		cout<<endl;
	}
	for(int i = 0;i<sideLength;i++){cout<<" "<<flush;}
	for(int i = 0;i<=sideLength;i++){cout<<setw(3)<<"  "<<flush;}
	for(int i = 0;i<sideLength;i++){cout<<setw(3)<<computer<<flush;}
	cout<<endl;
	for(int i = 0;i<sideLength;i++){cout<<" "<<flush;}
	for(int i = 0;i<=sideLength;i++){cout<<setw(3)<<"  "<<flush;}
	for(int i = 0;i<sideLength;i++){cout<<setw(3)<<i<<flush;}
	cout<<endl;
	for (int i = 0; i<sideLength; i++){cout<<"---------"<<flush;}
	cout<<endl;
}

void Game::PlayerTurn(){
	int unsigned x,y;
	cout<<endl;
	cout<<"Your turn! Chose place to set up your presence(^ROW^ ->COLUMN<-= ) "<<flush;
	cout<<endl;
	bool proper = 0;
	while(!proper){
		cin >> y >> x;
		cin.clear();
		cout<<"Value of X = "<<x<<" Value of Y = "<<y<<endl;
		if(board1->isValidSpace(x,y)&&board1->MovePossibleCheck(x,y)){
			board1->SetHex(x,y,playerColor);
			proper = 1;
		}
		else{
			cout<<"Wrong address!"<<endl;
		}
	}
}
void Game::ComputerTurn(){
	int unsigned x,y;
	cout<<"AI Turn!"<<flush;
	cout<<endl;
	bool proper = 0;
	while(!proper){
		x = rand() % board1->getSideSize();
		y = rand() % board1->getSideSize();
		if(board1->isValidSpace(x,y)&&board1->MovePossibleCheck(x,y)){
			board1->SetHex(x,y,computerColor);
			proper = 1;
		}
		else{
			cout<<"Wrong address!"<<endl;
		}
	}
}
bool Game::CheckWin(bool isAI){
	State currState;
	Player currPlayer;

	if(!isAI){
		currState = playerColor;
		currPlayer = player;
	}
	else if(isAI){
		currState = computerColor;
		currPlayer = computer;
	}

	////Create matrix of current connections between Hexes
	size = board1->getSideSize() * board1->getSideSize() + 4;
	int sideLength = board1->getSideSize();
	//Create the external "nodes" (where we measure if there is connection)
	//aka the sides of the board
	int  top = size - 4;
	int  bottom = size - 3;
	int left = size - 2;
	int right = size - 1;
	pair<int, int> address;
	int x, y;
	graphArray.resize(size);
	for (int row=0;row<size;row++){graphArray[row].resize(size,INF);}
	for(int row = 0; row < size; row++){
		for(int column = 0; column<size;column++){
			graphArray[row][column]=INF;
			if(row==column){graphArray[row][column]=0;}
		}
	}
	for (unsigned int i = 0; i < (size - 4); i++) {
		address = board1->indexToXY(i);
		x = address.first;
		y = address.second;

		//x-1, y
		if ((board1->isValidSpace(x - 1, y))&&(board1->HexState(x-1,y) == currState)
		)
		{
			graphArray[i][board1->getIndex(x - 1, y)] = 1;
			graphArray[board1->getIndex(x - 1, y)][i] = 1;
		}
		//x+1, y
		else if ((board1->isValidSpace(x + 1, y))&&(board1->HexState(x+1,y) == currState)
		)
		{
			graphArray[i][board1->getIndex(x + 1, y)] = 1;
			graphArray[board1->getIndex(x + 1, y)][i] = 1;
		}

		//x, y-1
		else if ((board1->isValidSpace(x, y-1))&&(board1->HexState(x,y-1) == currState)
		)
		{
			graphArray[i][board1->getIndex(x, y-1)] = 1;
			graphArray[board1->getIndex(x, y-1)][i] = 1;
		}
		//x+1, y-1
		else if ((board1->isValidSpace(x+1, y-1))&&(board1->HexState(x+1,y-1) == currState)
		)
		{
			graphArray[i][board1->getIndex(x+1, y-1)] = 1;
			graphArray[board1->getIndex(x+1, y-1)][i] = 1;
		}
		//x, y+1
		else if ((board1->isValidSpace(x, y+1))&&(board1->HexState(x,y+1) == currState)
		)
		{
			graphArray[i][board1->getIndex(x, y+1)] = 1;
			graphArray[board1->getIndex(x, y+1)][i] = 1;
		}
		//x-1, y+1
		else if ((board1->isValidSpace(x-1, y+1))&&(board1->HexState(x-1,y+1) == currState)
		)
		{
			graphArray[i][board1->getIndex(x-1, y+1)] = 1;
			graphArray[board1->getIndex(x-1, y+1)][i] = 1;
		}
	}

	for (unsigned int i = 0; i < sideLength; i++) {
		if (isAI){
			//Case for computer!

			if((board1->isValidSpace(i, 0)) &&(board1->HexState(i, 0) == currState)){
				graphArray[top][board1->getIndex(i, 0)] = 1;
				graphArray[board1->getIndex(i, 0)][top] = 1;
			}

			if((board1->isValidSpace(i, sideLength-1)) &&(board1->HexState(i, sideLength-1) == currState)){
				graphArray[bottom][board1->getIndex(i, sideLength-1)] = 1;
				graphArray[board1->getIndex(i, sideLength-1)][bottom] = 1;
			}

		}

		if (!isAI){
			//Case for player

			if((board1->isValidSpace(0,i)) &&(board1->HexState(0,i) == currState)){
				graphArray[left][board1->getIndex(0, i)] = 1;
				graphArray[board1->getIndex(0, i)][left] = 1;
			}

			if((board1->isValidSpace(sideLength-1,i)) &&(board1->HexState(sideLength-1,i) == currState)){
				graphArray[right][board1->getIndex(sideLength-1,i)] = 1;
				graphArray[board1->getIndex(sideLength-1,i)][right] = 1;
			}

		}
	}
	/*
	//Print the graph matrix!
	for(int row = 0; row < size; row++){
		cout<<row<<flush;
		for(int column = 0; column<size;column++){
			cout<< setw(2)<<graphArray[row][column] <<flush;
		}
		cout<<endl;
	}
	 */
	//Actual path algorithm
	int origin;
	int destination;

	if(!isAI){
		origin = left;
		destination = right;
	}
	else if(isAI){
		origin = top;
		destination = bottom;
	}

	int visited[size];
	int pathway[size];
	int mindistance;
	int nextnode= -1 ;
	int distance[size];
	for(int x=0;x<size;x++) {
		distance[x]=graphArray[origin][x];
		pathway[x]=origin;
		visited[x]=0;
	}
	distance[origin]=0;
	visited[origin]=1;
	int count=1;
	while(count<size-1) {
		mindistance=INF;
		for(int i=0;i<size;i++){
			if(distance[i]<mindistance&&!visited[i]) {
				mindistance=distance[i];
				nextnode=i;
			}}
		if(nextnode!=-1){visited[nextnode]=1;}

		for(int i=0;i<size;i++){
			if(!visited[i]){
				if(nextnode!=-1 && mindistance+graphArray[nextnode][i]<distance[i]) {
					distance[i]=mindistance+graphArray[nextnode][i];
					pathway[i]=nextnode;
				}}}
		count++;
	}

	cout<<endl;
	if(distance[destination]<INF)
	{
		if (isAI){cout<<"AI WON !"<<endl;}
		if (!isAI){cout<<"YOU WON!"<<endl;}
		return false;
	}

	//if (isAI){cout<<"AI Distance"<<endl;}
	//if (!isAI){cout<<"Player distance"<<endl;}
	//cout<<"The distance is!"<<(distance[destination])<<endl;

	return true;

}


#endif /* GAME_H_ */
