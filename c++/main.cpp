//
//  main.cpp
//  hw4_hexboard
//
//  Created by hexin xu on 2019/10/17.
//  Copyright © 2019 hexin xu. All rights reserved.
//
//  You are very welcomed to try :)

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <utility>
#include <string>
#include <ctime>
#include <cstdlib>
using namespace std;

#define BLANK 0
#define BLUE 1
#define RED 2   //define the colors, with blue to go first

class node
{
public:
    int color;  // 0 = blank, 1 = blue, 2 = red
    int edges;  //edge number connected to this node
    node(int edges_ = 6):edges(edges_){color = BLANK;}
};


class hexboard
{
private:
    const int rows;   //eg.7 or 11
    const static pair<int,int> neighbors[6];   //six neighbors' location relative to current node
    const char out_color[3] = {'.','B','R'};
public:
    node **board;
    hexboard(int rows_):rows(rows_)     //constuct a hexboard with given rows
    {
        board = new node*[rows];
        for(int i = 0;i < rows;i ++)
        {
            board[i] = new node[rows];
        }
    }

    bool placeNode(int row, int col, int placing);
    void checkboarder(int row, int col, bool &flag1, bool &flag2, int player);
    bool whoWins(int row, int col);
    bool simpleStep(int myturn);
    void printboard();
};


//When finding neighbors of a specific node, we only need to check whether its neighbor has exceeded the ranges
const pair<int,int> hexboard::neighbors[6] =
{
    {-1 , 0}, {-1 , 1},
    {0, -1}, {0, 1},
    {1, -1}, {1, 0}
};

bool hexboard::placeNode(int row, int col, int placing)
{
    if(row < 0 || row >= rows || col < 0 || col >= rows)  //index out-of-range
        return false;

    if(board[row][col].color != BLANK)   //if there is piece on the node already
        return false;

    board[row][col].color = placing;

    return true;
}

//check whether a node is at the boarders
void hexboard::checkboarder(int row, int col, bool &flag1, bool &flag2, int player)
{
    if(player == BLUE)
    {
        if(col == 0)
            flag1 = true;
        if(col == rows - 1)
            flag2 = true;
    }
    if(player == RED)
    {
        if(row == 0)
            flag1 = true;
        if(row == rows - 1)
            flag2 = true;
    }
}

// BFS to check whether one side has won after placing a piece
bool hexboard::whoWins(int row, int col)
{
    if(row >= rows || row < 0 || col < 0 || col >= rows)
        return false;
    int player = board[row][col].color;
    bool flag1 = false, flag2 = false;
    vector< vector<bool> > visited(rows, vector<bool>(rows));
    for(int i = 0; i < rows; i ++)
        for(int j = 0; j < rows; j ++)
            visited[i][j] = false;
    queue<pair<int, int>> q;
    q.push(make_pair(row, col));
    visited[row][col] = true;
    // bfs and check boarders of the path
    while(!q.empty())
    {
        auto top = q.front();
        checkboarder(top.first, top.second, flag1, flag2, player);
        q.pop();
        for(int i = 0; i < 6; i ++)
        {
            int cur_r = top.first + neighbors[i].first;
            int cur_c = top.second + neighbors[i].second;
            if(cur_r < 0 || cur_r >= rows || cur_c < 0 || cur_c >= rows )   //out-of-range pass
                continue;
            else
            {
                if(board[cur_r][cur_c].color == player && visited[cur_r][cur_c] == false)
                {
                    visited[cur_r][cur_c] = true;
                    q.push(make_pair(cur_r, cur_c));
                }
            }
        }
    }

    return flag1 && flag2;
}

//random place the piece with myturn the color
bool hexboard::simpleStep(int myturn)
{
    srand(time(0));
    int r_, c_;
    do
    {
        r_ = rand() % rows;
        c_ = rand() % rows;
    }while(!this->placeNode(r_, c_, myturn));

    cout << "Player " << myturn << ": (" << (r_ + 1) << ", " << (c_ + 1) <<")." << endl;
    if(this->whoWins(r_, c_))
    {
        cout << "Computer wins. See you next time." << endl;
        return true;
    }
    else
        return false;

}



//print out the hexboard with ASCII
void hexboard::printboard()
{
    string lines = "\\";    //lines are the same between nodes
    cout << out_color[board[0][0].color];
    for(int i = 1;i < rows;i ++)
    {
        cout << " - " << out_color[board[0][i].color];
        lines += " / \\";
    }
    cout << endl;
    string space = "";   //space record the indent of each line
    for(int i = 1;i < rows;i ++)
    {
        space += " ";
        cout << space << lines << endl;
        space += " ";
        cout << space << out_color[board[i][0].color];
        for(int j = 1;j < rows;j ++)
        {
            cout << " - " << out_color[board[i][j].color];
        }
        cout << endl;
    }
}

//main interact function
int main()
{
    int size;
    cout << "Please enter the size of hex board:" ;
    cin >> size;
    hexboard myboard(size);
    cout << "Initial hex board..." << endl;
    myboard.printboard();
    cout << "With player Blue first to go, do you want Blue(1) or Red(2)? Please enter 1 or 2." << endl;
    int client, myside;
    cin >>client;
    myside = 3 - client;
    cout <<"Game started." << endl;
    cout <<"Please enter the location you want to place like this: 2 3, within range 1 to " << size << endl;

    if(myside == 1)   // if computer goes first
        myboard.simpleStep(myside);
    else
    {
        while(true)
        {
            // player goes first
            int x, y;
            cin >> x >> y;
            x --; y --;      //input is out of range
            while(!myboard.placeNode(x, y, client))
            {
                cout << "Oops, wrong place! Try another one." << endl;
                cin >> x >> y;
                x--; y--;
            }
            cout << "Player " << client << ": (" << x + 1 << ", " << y + 1 <<")." << endl;
            if(myboard.whoWins(x, y))
            {
                cout << "Congratulations! You win!" << endl;
                break;
            }

            //computer's turn
            if(myboard.simpleStep(myside))
                break;

            myboard.printboard();    //print current board after every step each
        }
    }
    return 0;
}
