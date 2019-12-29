/*
 * Board.h
 *
 *  Created on: Oct 12, 2019
 *      Author: michalkozinski
 */

#ifndef BOARD_H_
#define BOARD_H_
#include <vector>
#include <utility>
#include <iomanip>
#include <cstdlib>
#include <ctime>

using namespace std;
const int INF = 999;

//Create Enum class for possible hex states
enum class State: short{H_EMPTY, H_RED, H_BLUE};
enum class Player: short{P_RED, P_BLUE};
ostream& operator<<(ostream& out, const State&s){

	if (s == State::H_EMPTY){
		return(out<<"*");
	}
	else if (s == State::H_RED){
		return(out<<"R");
	}
	else if (s == State::H_BLUE){
		return(out<<"B");
	}else{
		return(out<<"X");
	}
}

ostream& operator<<(ostream& out, const Player&s){
	if (s == Player::P_BLUE){
		return(out<<"B");
	}
	else if (s == Player::P_RED){
		return(out<<"R");
	}
	else{
		return(out<<"*");
	}
}
/*Create Board class of given size with all hexes set to State::H_Empty
 * and all functions that I might need to use during the game development.
 * Used a simple vector structure as its fast and should allow me easily develop game.
 */
class Board {
private:
	int sideLength;
	vector<State>* board;
public:
	Board(){};
	Board(int givenSideLength);
	Board(Board const &oldBoard);
	virtual ~Board();
	inline int getSize() const{return board->size();}
	inline int getSideSize() const{return sideLength;}
	inline int getIndex(unsigned int y, unsigned int x) const;
	inline bool isValidSpace(unsigned int x, unsigned int y) const;
	inline bool isValidSpace(unsigned int vectorIndex) const;
	inline bool MovePossibleCheck(unsigned int x, unsigned int y) const;
	inline bool MovePossibleCheck(unsigned int index) const;
	inline State HexState(unsigned int index) const;
	inline State HexState(unsigned int x, unsigned int y) const;
	inline void SetHex(unsigned int index, State ST);
	inline void SetHex(unsigned int x, unsigned int y, State ST);
	inline pair<int,int> indexToXY(unsigned int index) const;
};
Board::Board(int givenSideLength) {
	//Board Constructor
	sideLength = givenSideLength;
	board = new vector<State>(sideLength * sideLength, State::H_EMPTY);
}
Board::Board(Board const &oldBoard): sideLength(oldBoard.sideLength){
	board = new vector<State>(*(oldBoard.board));
}
Board::~Board() {
	delete board;
}

inline int Board::getIndex(unsigned int x, unsigned int y) const {
	return (sideLength*y + x);
}
inline bool Board::isValidSpace(unsigned int x, unsigned int y) const {
	return (x < sideLength && y < sideLength );
}
inline bool Board::isValidSpace(unsigned int vectorIndex) const {
	return (vectorIndex < board->size());
}
inline State Board::HexState(unsigned int index) const{
	return (((*board) [index]));
}
inline State Board::HexState(unsigned int x, unsigned int y) const{
	return(HexState(getIndex(x,y)));
}
inline bool Board::MovePossibleCheck(unsigned int x, unsigned int y) const{
	return(isValidSpace(x,y) && HexState(x,y) == State::H_EMPTY);
}
inline bool Board::MovePossibleCheck(unsigned int index) const{
	return(isValidSpace(index) && HexState(index) == State::H_EMPTY);
}
inline void Board::SetHex(unsigned int index, State ST){
	((*board) [index]) = ST;
}
inline void Board::SetHex(unsigned int x, unsigned int y, State ST){
	SetHex(getIndex(x,y),ST);
}
inline pair<int,int> Board::indexToXY(unsigned int index) const{
	int y = index / sideLength;
	int x = index % sideLength;
	return(make_pair(x,y));
}



#endif /* BOARD_H_ */
