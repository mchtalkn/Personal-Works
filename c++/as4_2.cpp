#include <iostream>
#include <vector>
#include <random>
#include <ctime>
#include <algorithm>
#include <chrono>
#include <iterator>
using namespace std;

class Node{
public:
  Node(int val=0):value(val){}
  int  getVal() const {return value;}
  // returns owner of this node
  void setVal(int val){value=val;}
  // sets owner of this node
  int getEdge(int n){
    if(n>edges.size()-1) return -1;
    else return edges[n];
  }
  //retuns neighbors of this node
  void setEdge(int n){edges.push_back(n);}
  // adds neighbor to this node
  int getSize(){return edges.size();}
  //returns how much neighbor that node have
  ~Node(){ }
private:
  int value;
  vector<int> edges;
};
ostream & operator <<(ostream &out,const Node &n){
  switch (n.getVal()) {
    case 0: {cout <<".";break;}
    case 1: {cout <<"X";break;}
    case 2: {cout <<"O";break;}
  }
  return out;
}

class hexGraph{
public:
  hexGraph(int n);
  hexGraph(const hexGraph &hexg);
  // takes one dimension creates hex board
  short move(int i,int j, int player);
  // player's move to (i-j)
  short removeH(int i,int j);
  vector<int> getFreeNodes(){
    return freeNodes;
  }
  int getSize(){
    return size;
  }
  short whoWon();
  //return who won this game 0 for draw
  void print();
  //prints board
  ~hexGraph(){}
private:
  short winnerHelper(int i,int player,int caller);
  //helper for recursive whoWon
  int size;
  vector<Node> nodeList;
  vector<int> freeNodes;
};
hexGraph::hexGraph(int n=0){
  int count=0;
  size=n;
  nodeList.resize(n*n);
  for(int i=0;i<n;i++){
    for(int j=0;j<n;j++){
      freeNodes.push_back(i*n+j);
      if(i>0){
        if(j>0){
          nodeList[count].setEdge((i-1)*n+j-1);
        }else;
        nodeList[count].setEdge((i-1)*n+j);
        if(j<(n-1)){
          nodeList[count].setEdge((i-1)*n+j+1);
        }else;
      }else;
        if(j>0){
          nodeList[count].setEdge(i*n+j-1);
        }else;
        if(j<(n-1)){
          nodeList[count].setEdge(i*n+j+1);
        }else;
        if (i<(n-1)){
          if(j>0){
            nodeList[count].setEdge((i-1)*n+j-1);
          }else;
          nodeList[count].setEdge((i-1)*n+j);
          if(j<(n-1)){
            nodeList[count].setEdge((i-1)*n+j+1);
          }else;
        }else;
        count++;
    }
  }
}
hexGraph::hexGraph(const hexGraph &hexg){
  size=hexg.size;
  nodeList=hexg.nodeList;
  freeNodes=hexg.freeNodes;
}

void hexGraph :: print(){
  for(int i=0;i<size;i++){
    for(int m=0;m<i;m++) cout<<" ";
    for (int j=0;j<size;j++){
      cout<<nodeList[i*size+j];
      if(j==size-1) break;
      cout<<"-";
    }
    cout<<endl;
    for(int m=0;m<i+1;m++) cout<<" ";
    if(i<(size-1)){
      for (int j=0;j<size-1;j++){
        cout<<"\\/";
      }
    }
    cout<<endl;
  }
}

short hexGraph :: move(int i, int j,int player){
  if(i>=size || j>=size||i<0||j<0){
    if(player=2) return 0;
    // comonnet above part for 2 player
    cout<<"impossible move"<<endl;
    return 0;
  }
  else if(nodeList[i*size+j].getVal()==0){
    nodeList[i*size+j].setVal(player);
    //freeNodes.erase(std::remove(freeNodes.begin(),freeNodes.end(),i*size+j),freeNodes.end());
    return 1;
  }else{
    if(player=2) return 0;
    // comment above part for 2 player game
    cout<<"impossible move"<<endl;
    return 0;
  }
}
short hexGraph :: removeH(int i,int j){
    if(i>=size || j>=size||i<0||j<0){
      cerr<<"out of range";
      return -1;
    }
    else{
      nodeList[i*size+j].setVal(0);
      freeNodes.push_back(i*size+j);
      return 0;
    }
}

short hexGraph :: whoWon(){
  short m=0;
  for (int i=0;i<size;i++){
    m+=winnerHelper(i*size,1,-1);
  }
  if(m) return 1;
  for (int j=0;j<size;j++){
    m+=winnerHelper(j,2,-1);
  }
  if(m) return 1;
  return 0;
}
short hexGraph :: winnerHelper(int i, int player, int caller){
  int target;
  short m=0;
  if (player==1){
    if ((nodeList[i]).getVal()!=1) return 0;
    else if ((i%size)==(size-1)) return 1;
    else {
    for(int n=0;n<nodeList[i].getSize();n++){
      target=nodeList[i].getEdge(n);
      if(target==caller || target%size<i%size) continue;
      m+=winnerHelper(target,1,i);
    }
    return m;
    }
  }
  else {
    if (nodeList[i].getVal()!=2) return 0;
    else if ((i)>=size*(size-1)) return 1;
    else {
    for(int n=0;n<nodeList[i].getSize();n++){
      target=nodeList[i].getEdge(n);
      if(target==caller || target/size<i/size) continue;
      m+=winnerHelper(target,2,i);
    }
    return m;
    }
  }
  cout<<"checked"<<endl;
}
int main(){
  int i,j,moveCounter=0,moveP;
  int n=5;
  char character;
  hexGraph x(n);
// below part is for 2 player game
/*while(!x.whoWon()){
  cin>>i>>character>>j;
  if(x.move(i,j,moveCounter%2+1)) moveCounter++;
  else;
  x.print();
}*/
while(!x.whoWon()){
  cout<<"player:"<<moveCounter%2+1<<endl;
  srand(time(NULL));
  if (!(moveCounter%2)){
    cin>>i>>character>>j;
    // format is like 1-4
    if(x.move(i,j,1)) moveCounter++;
    else continue;
    x.print();
  }
  else {
    moveP=rand()%25;
    if(x.move(moveP/n,moveP%n,2)) moveCounter++;
    else continue;
    x.print();
  }

}
cout<<"winner is player "<<x.whoWon();
  return 0;
}
