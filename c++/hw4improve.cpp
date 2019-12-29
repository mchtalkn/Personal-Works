// main.cpp
#include <iostream>
#include "Game.h"

using namespace std;

int main()
{
    graph test;

    Game g(test);

    g.playGame();
    return 0;
}

// Game.h
#ifndef GAME_H
#define GAME_H
#include <iostream>
#include "graph.h"

class Game
{
    public:
        Game(graph& b): board(b){};
        graph getBoard() { return board;}
        void playGame();
    private:
        graph board;
};

#endif // GAME_H

// Game.cpp
#include <iostream>
#include <vector>
#include "Game.h"

void Game::playGame()
{
    std::cout << "Starting a game of Hex ..." << std::endl;
    std::cout << getBoard();
    char player = 'B';

    for (int turn = 1; turn <= 121; turn++) {
        if (player == 'B' && turn > 1) player = 'R';
        else player = 'B';
        board.setPlayerMove(player);
        std::cout << getBoard();

        if (board.checkVictory(player)) {
            std::cout << "Player " << player << " wins ...!" << std::endl;
            break;
        }
    }
}

// graph.h
#ifndef GRAPH_H
#define GRAPH_H
#include <iostream>
#include <vector>
#include "node.h"

class graph
{
    public:
        graph();
        void resetBoard();
        bool checkBlocked(node, char);
        bool isFull();
        void setPlayerMove(char);
        bool checkVictory(char);
        bool checkPathW(std::vector<std::vector<bool>>&, node, node);
        bool checkPathB(std::vector<std::vector<bool>>&, node, node);
        friend std::ostream& operator<<(std::ostream& out, const graph& g);
        char getEntryAt(int, int);
        node getNodeAt(int, int);

        bool waitForPlayer() { return waitingForPlayer;}
        void setWaitingForPlayer(bool waiting) { waitingForPlayer = waiting;}
        char getPlayer() { return player;}
        void setPlayer(char e) {player = e; }
        char getWinner() { return winner;}
        void setWinner(char w) { winner = w;}

    private:
        bool waitingForPlayer;
        char player;
        char winner;
        std::vector<std::vector<node>> board;
};

#endif // GRAPH_H

// graph.cpp
#include <iostream>
#include <vector>
#include "graph.h"

graph::graph()
{
    board.resize(11);
    for (int i =0; i < 11; i++) board[i].resize(11);
    for (int i = 0; i < 11; i++)
        for (int j = 0; j < 11; j++)
          board[i][j] = node(i,j);
    player = '0';
    winner = '0';
}


bool graph::checkBlocked(node curnode, char player) {
     int r = curnode.getRow();
     int c = curnode.getCol();

     // top, r= 0, c = 0
     if (r ==0 && c ==0 &&
         ( (board[r+1][c].getEntry() == '-') || (board[r][c+1].getEntry() == '-')
        || (board[r+1][c].getEntry() == player) || (board[r][c+1].getEntry() == player)))
        return false;

      // top, r=0, c=1->9
      if (r ==0 && c !=0 && c!=10 &&
         ( (board[r][c-1].getEntry() == '-') || (board[r][c+1].getEntry() == '-')
        || (board[r+1][c-1].getEntry() == '-') || (board[r+1][c].getEntry() == '-')
        || (board[r][c-1].getEntry() == player) || (board[r][c+1].getEntry() == player)
        || (board[r+1][c-1].getEntry() == player) || (board[r+1][c].getEntry() == player)
          ))
        return false;

    // top, r= 0, c= 10
       if (r ==0 && c==10 &&
         ( (board[r][c-1].getEntry() == '-') || (board[r+1][c-1].getEntry() == '-')
        || (board[r+1][c].getEntry() == '-')
        || (board[r][c-1].getEntry() == player) || (board[r+1][c-1].getEntry() == player)
        || (board[r+1][c].getEntry() == player))
          )
        return false;

    // bottom, r= 10, c= 0
      if (r ==10 && c==0 &&
         ( (board[r-1][c].getEntry() == '-') || (board[r-1][c+1].getEntry() == '-')
        || (board[r][c+1].getEntry() == '-')
        || (board[r-1][c].getEntry() == player) || (board[r-1][c+1].getEntry() == player)
        || (board[r][c+1].getEntry() == player))
          )
        return false;

      // bottom, r= 10, c= 1->9
      if (r ==10 && c!=0 && c!=9 &&
         ( (board[r][c-1].getEntry() == '-') || (board[r][c+1].getEntry() == '-')
        || (board[r-1][c].getEntry() == '-') || (board[r-1][c+1].getEntry() == '-')
        || (board[r][c-1].getEntry() == player) || (board[r][c+1].getEntry() == player)
        || (board[r-1][c].getEntry() == player) || (board[r-1][c+1].getEntry() == player))
          )
        return false;

      //bottom r=10, c= 10
       if (r ==10 && c==10 &&
         ( (board[r-1][c].getEntry() == '-') || (board[r][c-1].getEntry() == '-')
        || (board[r-1][c].getEntry() == player) || (board[r][c-1].getEntry() == player))
          )
        return false;

      // left r=1->9, c = 0
       if (r!=0 && r !=10 && c==0 &&
         ( (board[r-1][c].getEntry() == '-') || (board[r-1][c+1].getEntry() == '-')
        || (board[r][c+1].getEntry() == '-') || (board[r+1][c].getEntry() == '-')
        || (board[r-1][c].getEntry() == player) || (board[r-1][c+1].getEntry() == player)
        || (board[r][c+1].getEntry() == player) || (board[r+1][c].getEntry() == player))
          )
        return false;

      // right r = 1->9, c= 10
       if (r!=0 && r !=10 && c==10 &&
         ( (board[r-1][c].getEntry() == '-') || (board[r][c-1].getEntry() == '-')
        || (board[r+1][c-1].getEntry() == '-') || (board[r+1][c].getEntry() == '-')
        || (board[r-1][c].getEntry() == player) || (board[r][c-1].getEntry() == player)
        || (board[r+1][c-1].getEntry() == player) || (board[r+1][c].getEntry() == player))
          )
        return false;

      // inner
        if (r!=0 && r!=10 && c!=0 && c!=10 &&
         ( (board[r-1][c].getEntry() == '-') || (board[r-1][c+1].getEntry() == '-')
        || (board[r][c+1].getEntry() == '-') || (board[r][c-1].getEntry() == '-')
        || (board[r+1][c-1].getEntry() == '-') || (board[r+1][c].getEntry() == '-')
        || (board[r-1][c].getEntry() == player) || (board[r-1][c+1].getEntry() == player)
        || (board[r][c+1].getEntry() == player) || (board[r][c-1].getEntry() == player)
        || (board[r+1][c-1].getEntry() == player) || (board[r+1][c].getEntry() == player) )
          )
        return false;

    return true;
}

bool graph::isFull() {
   for (int r = 0; r < 11; r++) {
      for (int c = 0; c < 11; c++) {
          if (board[r][c].getEntry() == '-') return false;
      }
   }
   return true;
}


void graph::resetBoard() {
  for (int i = 0; i < 11; i++) {
        for (int j = 0; j < 11; j++) {
          board[i][j].setEntry('-');
          for (int k =0; k < 6; k++)
            board[i][j].setConnection(k, NULL);
        }
  }
  waitingForPlayer = true;
  player = '0';
  winner = '0';
}

void graph::setPlayerMove(char e) {
    bool placed = false;
    bool oob = false;
    int r, c;

    while (!placed) {
        oob = false;
        std::cout << "Please enter the row number" << std::endl;
        std::cin>> r;
        std::cout << "Please enter the column number" << std::endl;
        std::cin>> c;

        if (r > 10 || r < 0 || c > 10 || c < 0) oob = true;
        if (!oob && !checkBlocked(getNodeAt(r, c), e) && board[r][c].getEntry()=='-') {
            board[r][c].setEntry(e);
            placed = true;
        }
    }

    // set connections amongst different nodes here
      // top, r= 0, c = 0
     if (r ==0 && c ==0) {
        if (board[r+1][c].getEntry() == e) {
            board[r][c].setConnection(3, &board[r+1][c]);
            board[r+1][c].setConnection(0, &board[r][c]);
        }
        if (board[r][c+1].getEntry() == e) {
            board[r][c].setConnection(2, &board[r][c+1]);
            board[r][c+1].setConnection(5, &board[r][c]);
        }
     }


      // top, r=0, c=1->9
      if (r ==0 && c !=0 && c!=10) {

          if (board[r][c-1].getEntry() == e) {
            board[r][c].setConnection(5, &board[r][c-1]);
            board[r][c-1].setConnection(2, &board[r][c]);
          }

          if (board[r][c+1].getEntry() == e) {
            board[r][c].setConnection(2, &board[r][c+1]);
            board[r][c+1].setConnection(5, &board[r][c]);
          }
          if (board[r+1][c-1].getEntry() == e) {
            board[r][c].setConnection(4, &board[r+1][c-1]);
            board[r+1][c-1].setConnection(1, &board[r][c]);
          }
          if (board[r+1][c].getEntry() == e) {
            board[r][c].setConnection(3, &board[r+1][c]);
            board[r+1][c].setConnection(0, &board[r][c]);
          }

      }

    // top, r= 0, c= 10
       if (r ==0 && c==10) {
        if (board[r][c-1].getEntry() == e) {
            board[r][c].setConnection(5, &board[r][c-1]);
            board[r][c-1].setConnection(2, &board[r][c]);
        }
        if (board[r+1][c-1].getEntry() == e) {
            board[r][c].setConnection(4, &board[r+1][c-1]);
            board[r+1][c-1].setConnection(1, &board[r][c]);
        }
        if (board[r+1][c].getEntry() == e) {
            board[r][c].setConnection(3, &board[r+1][c]);
            board[r+1][c].setConnection(0, &board[r][c]);
        }
       }
    // bottom, r= 10, c= 0
      if (r ==10 && c==0) {
        if (board[r-1][c].getEntry() == e) {
            board[r][c].setConnection(0, &board[r-1][c]);
            board[r-1][c].setConnection(3, &board[r][c]);
        }
        if (board[r-1][c+1].getEntry() == e) {
            board[r][c].setConnection(1, &board[r-1][c+1]);
            board[r-1][c+1].setConnection(4, &board[r][c]);
        }
        if (board[r][c+1].getEntry() == e) {
            board[r][c].setConnection(2, &board[r][c+1]);
            board[r][c+1].setConnection(5, &board[r][c]);
        }
      }

      // bottom, r= 10, c= 1->9
      if (r ==10 && c!=0 && c!=9) {
         if (board[r][c-1].getEntry() == e) {
            board[r][c].setConnection(5, &board[r][c-1]);
            board[r][c-1].setConnection(2, &board[r][c]);
         }
         if (board[r][c+1].getEntry() == e) {
            board[r][c].setConnection(2, &board[r][c+1]);
            board[r][c+1].setConnection(5, &board[r][c]);
         }
         if (board[r-1][c].getEntry() == e) {
            board[r][c].setConnection(0, &board[r-1][c]);
            board[r-1][c].setConnection(3, &board[r][c]);
         }
         if (board[r-1][c+1].getEntry() == e) {
            board[r][c].setConnection(1, &board[r-1][c+1]);
            board[r-1][c+1].setConnection(4, &board[r][c]);
         }
      }


      //bottom r=10, c= 10
       if (r ==10 && c==10) {
        if (board[r-1][c].getEntry() == e) {
            board[r][c].setConnection(0, &board[r-1][c]);
            board[r-1][c].setConnection(3, &board[r][c]);
        }
        if (board[r][c-1].getEntry() == e) {
            board[r][c].setConnection(5, &board[r][c-1]);
            board[r][c-1].setConnection(2, &board[r][c]);
        }
       }

      // left r=1->9, c = 0
       if (r!=0 && r !=10 && c==0) {
        if (board[r-1][c].getEntry() == e) {
            board[r][c].setConnection(0, &board[r-1][c]);
            board[r-1][c].setConnection(3, &board[r][c]);
        }
        if (board[r-1][c+1].getEntry() == e) {
            board[r][c].setConnection(1, &board[r-1][c+1]);
            board[r-1][c+1].setConnection(4, &board[r][c]);
        }
        if (board[r][c+1].getEntry() == e) {
            board[r][c].setConnection(2, &board[r][c+1]);
            board[r][c+1].setConnection(5, &board[r][c]);
        }
        if (board[r+1][c].getEntry() == e) {
            board[r][c].setConnection(3, &board[r+1][c]);
            board[r+1][c].setConnection(0, &board[r][c]);
        }
    }
      // right r = 1->9, c= 10
       if (r!=0 && r !=10 && c==10) {
        if (board[r-1][c].getEntry() == e) {
            board[r][c].setConnection(0, &board[r-1][c]);
            board[r-1][c].setConnection(3, &board[r][c]);
        }
        if (board[r][c-1].getEntry() == e) {
            board[r][c].setConnection(5, &board[r][c-1]);
            board[r][c-1].setConnection(2, &board[r][c]);
        }
        if (board[r+1][c-1].getEntry() == e) {
            board[r][c].setConnection(4, &board[r+1][c-1]);
            board[r+1][c-1].setConnection(1, &board[r][c]);
        }
        if (board[r+1][c].getEntry() == e) {
            board[r][c].setConnection(3, &board[r+1][c]);
            board[r+1][c].setConnection(0, &board[r][c]);
        }

       }

      // inner
        if (r!=0 && r!=10 && c!=0 && c!=10) {
          if (board[r-1][c].getEntry() == e) {
            board[r][c].setConnection(0, &board[r-1][c]);
            board[r-1][c].setConnection(3, &board[r][c]);
          }
          if (board[r-1][c+1].getEntry() == e) {
            board[r][c].setConnection(1, &board[r-1][c+1]);
            board[r-1][c+1].setConnection(4, &board[r][c]);
          }
          if (board[r][c+1].getEntry() == e) {
            board[r][c].setConnection(2, &board[r][c+1]);
            board[r][c+1].setConnection(5, &board[r][c]);
          }
          if (board[r][c-1].getEntry() == e) {
            board[r][c].setConnection(5, &board[r][c-1]);
            board[r][c-1].setConnection(2, &board[r][c]);
          }
          if (board[r+1][c-1].getEntry() == e) {
            board[r][c].setConnection(4, &board[r+1][c-1]);
            board[r+1][c-1].setConnection(1, &board[r][c]);
          }
          if (board[r+1][c].getEntry() == e) {
            board[r][c].setConnection(3, &board[r+1][c]);
            board[r+1][c].setConnection(0, &board[r][c]);
          }
        }

}

bool graph::checkVictory(char player) {

    // W goes west to eat
    // B goes north to south

    std::vector<std::vector<bool>> visited(11, std::vector<bool>(11, false));

    node start, goal;

    if (player == 'B') {

      for (int west = 0; west < 11; west++) {
          start = board[west][0];

          if (start.getEntry() == 'B' && !visited[west][0]) {
              for (int east = 0; east < 11; east++) {
                   goal = board[east][10];
                   if (goal.getEntry() == 'B' && (checkPathW(visited, start, goal))) {
                        winner = 'B';
                        return true;

                   }
              }
          }

        visited[west][0] = true;
      }

    }

    if (player == 'R') {

     for (int north = 0; north < 11; north++) {
          start = board[0][north];

          if (start.getEntry() == 'R' && !visited[0][north]) {
              for (int south = 0; south < 11; south++) {
                   goal = board[10][south];
                   if (goal.getEntry() == 'R' && (checkPathB(visited, start, goal))) {
                        winner = 'R';
                        return true;
                   }
              }
          }

        visited[0][north] = true;
      }
    }

    return false;
}

bool graph::checkPathW(std::vector<std::vector<bool>> &visited, node start, node goal) {

    int r = start.getRow();
    int c = start.getCol();
    visited[r][c] = true;

    for (int i = 0; i < 6; i++) {
    if ( c == 10 || (r == goal.getRow() && c == goal.getCol())) return true;
    if (start.getConnection(i)!=NULL && !visited[start.getConnection(i)->getRow()][start.getConnection(i)->getCol()]) {
         if (checkPathW(visited, *start.getConnection(i), goal)) return true;
    }
  }
   return false;
}


bool graph::checkPathB(std::vector<std::vector<bool>> &visited, node start, node goal) {

    int r = start.getRow();
    int c = start.getCol();
    visited[r][c] = true;

    for (int i = 0; i < 6; i++) {
    if ( r == 10 || (r == goal.getRow() && c == goal.getCol())) return true;
    if (start.getConnection(i)!=NULL && !visited[start.getConnection(i)->getRow()][start.getConnection(i)->getCol()]) {
         if (checkPathB(visited, *start.getConnection(i), goal)) return true;
    }
  }
   return false;
}

char graph::getEntryAt(int r, int c) {
   return board[r][c].getEntry();
}

node graph::getNodeAt(int r, int c) {
   return board[r][c];
}

std::ostream& operator<<(std::ostream& out, const graph& g) {
  std::vector< std::vector<node> >temp = g.board;
  out << " " << std::endl;
  for (int i = 0; i < 11; i++) std::cout << i << " ";
  out << std::endl;
  for (int r = 0; r < 11; r++) {

    for (int s = 0; s < r; s++) {
        if (s!=9) out << " ";
    }
    out << r << " ";

    for (int c = 0; c < 11; c++) {
        out << temp[r][c].getEntry() <<  " ";
    }
    out << std::endl;

  }

  return out;
}

// node.h
#ifndef NODE_H
#define NODE_H

#include <ctime>
#include <iostream>
#include <vector>
#include <cstdlib>

class node
{
    public:
        node(int r = 0, int c = 0, char e = '-');
        int getRow();
        void setRow(int);
        int getCol();
        void setCol(int);
        char getEntry();
        void setEntry(char);
        node* getConnection(int);
        void setConnection(int, node*);
        bool isConnected(node);

    private:
        int row, col;
        char entry;
        std::vector<node*> neighborlist;
};

#endif // NODE_H

// node.cpp
#include <iostream>
#include <vector>
#include "node.h"

node::node(int r, int c, char e) {
   neighborlist.resize(6);

   row = r;
   col = c;
   entry = e;
   if (row == 0)
       neighborlist[0] = NULL, neighborlist[1] = NULL;
   if (col == 0)
       neighborlist[4] = NULL, neighborlist[5] = NULL;
   if (row == 10)
       neighborlist[3] = NULL, neighborlist[4] = NULL;
   if (col == 10)
       neighborlist[1] = NULL, neighborlist[2] = NULL;
}

int node::getRow() {
   return row;
}
void node::setRow(int r) {
   row = r;
}

int node::getCol() {
   return col;
}
void node::setCol(int c) {
   col = c;
}

char node::getEntry() {
   return entry;
}
void node::setEntry(char e) {
   entry = e;
}

node* node::getConnection(int pos) {
   return neighborlist[pos];
}

void node::setConnection(int pos, node* neighbor) {
    neighborlist[pos] = neighbor;
}

bool node::isConnected(node curnode) {
     for (int i = 0; i < 6; i++) {
        node temp = *neighborlist[i];
        if (temp.getCol() == curnode.getCol() && temp.getRow() == curnode.getRow()) return true;
     }
     return false;
}
