#include <iostream>

#include <cstdlib>

#include <ctime>

#include <iterator>

#include <fstream>

#include <vector>

using namespace std;
struct edgeElement {
  int destination;
  int range;
  edgeElement * next;
};

class vertice {
  public:
    vertice() {
      head = NULL;
      cursor = NULL;
      id = 0;
    }
  vertice(int id): id(id) {
    head = NULL;
    cursor = NULL;
  }
  inline void set(int n) {
    id = n;
  }
  void addEdge(int destination, int range);
  int getEdge(int destination);
  inline edgeElement * popEdge() {
    edgeElement * temp;
    temp = cursor;
    if (cursor != NULL) {
      cursor = cursor -> next;
    } else;
    return temp;
  }
  inline void init() {
    cursor = head;
  }~vertice();
  private:
    edgeElement * head, * cursor;
  int id;
};

class graph {
  private:
  vertice * head;
  int cursor;
  int size;
  public:
    graph() {
      head = NULL;
      cursor = 0;
      size = 0;
    }
  graph(int n);
  graph(const char* p);
  graph(int n, double density, int maxRange, int minRange);
  void addEdge(int source, int destination, int range);
  inline int getsize(){
    return size;
  }
  vertice * getVertice(int id) {
    return &(head[id]);
  }~graph();
};

struct priorityQueElement {
  int id;
  int source;
  int priority;
  priorityQueElement * next;
};

class priorityQue {
  private:
    priorityQueElement * head, * cursor;
  public:
  priorityQue() {
      head = NULL;
      cursor = NULL;
    }
  priorityQueElement * popPQ();
  void pushPQ(int id,int source, int priority);
  bool isInclude(int id);
  int isShorter(int id, int priority);
  friend ostream& operator<<(ostream&out,const priorityQue &pQE);
  void changePriority(int id, int priority);
  ~priorityQue();
};
void vertice::addEdge(int destination, int range) {
  // adds a new edge from this vertice to given destination with given range
  edgeElement * tmp = new edgeElement;
  tmp -> destination = destination;
  tmp -> range = range;
  tmp -> next = NULL;
  if (head == NULL) {
    head = tmp;
    cursor = tmp;
  } else {
    tmp -> next = head;
    head = tmp;
    cursor = head;
  }
}
int vertice::getEdge(int destination) {
  //returns range from this vertice to given destination
  int range;
  cursor = head;
  while (cursor != NULL) {
    if (cursor -> destination == destination) {
      range = cursor -> range;
      cursor = head;
      return range;
    } else {
      cursor = cursor -> next;
    }
  }
  return 0;
}
vertice::~vertice() {
  cursor = head;
  while (head != NULL) {
    cursor = head -> next;
    delete head;
    head = cursor;
  }
}
priorityQueElement * priorityQue::popPQ() {
  priorityQueElement * temp;
  if (head == NULL) {
    return NULL;
  } else {
    temp = head;
    head = head -> next;
    return temp;
  }
}
void priorityQue::pushPQ(int id,int source, int priority) {
  //pushes element to priority que with given id and priority(range)
  priorityQueElement * elementP, * temp;
  cursor = head;
  elementP = new priorityQueElement;
  elementP -> id = id;
  elementP -> priority = priority;
  elementP -> source=source;
  elementP -> next = NULL;
  if (head == NULL) {
    head = elementP;
    cursor = head;
  } else if (head -> priority > priority) {
    elementP -> next = head;
    head = elementP;
    cursor = head;
  } else {
    while (cursor != NULL) {
      if (cursor -> next == NULL) {
        cursor -> next = elementP;
        break;
      } else if (cursor -> next -> priority > priority) {
        temp = cursor -> next;
        cursor -> next = elementP;
        elementP -> next = temp;
        break;
      } else {
        cursor = cursor -> next;
      }
    }
  }
  cursor = head;
}
bool priorityQue::isInclude(int id) {
  //returns if given element is exist or not
  cursor = head;
  while (cursor != NULL) {
    if (cursor -> id == id) {
      return 1;
    } else {
      cursor = cursor -> next;
    }
  }
  return 0;
}
void priorityQue::changePriority(int id, int priority) {
  //changes priority of given element
  cursor = head;
  while (cursor != NULL) {
    if (cursor -> id == id) {
      cursor -> priority = priority;
      break;
    } else {
      cursor = cursor -> next;
    }
  }
}
ostream& operator<<(ostream&out,const priorityQue &pQE){
  priorityQueElement *cursor;
  cursor=pQE.cursor;
  while(cursor!=NULL){
    out<<cursor->source<<"<--"<<cursor->priority<<"-->"<<cursor->id<<endl;
    cursor=cursor->next;
  }
  cursor=pQE.head;
  return out;
}
priorityQue::~priorityQue() {
  cursor = head;
  while (head != NULL) {
    cursor = head -> next;
    delete head;
    head = cursor;
  }
}
graph::graph(int n) {
  //creates a dummy graph with n nodes
  cursor = 0;
  head = new vertice[n];
  while (cursor < n) {
    head[cursor].set(cursor);
    cursor++;
  }
  cursor = 0;
  size = n;
}
graph::graph(int n, double density, int maxRange, int minRange) {
  //creates a graph with n nodes that are connected with given density and range
  int t = 0, random, range;
  cursor = 0;
  head = new vertice[n];
  while (cursor < n) {
    head[cursor].set(cursor);
    while (t < n - cursor) {
      random = rand() % 100;
      if (t == cursor) {
        t++;
        continue;
      } else if (random < density * 100) {
        range = (rand() % maxRange) + minRange;
        head[cursor].addEdge(t, range);
        head[t].addEdge(cursor, range);
        t++;
      } else {
        t++;
      }
    }
    t = 0;
    cursor++;
  }
  cursor = 0;
  size = n;
}
void graph::addEdge(int source, int destination, int range) {
  head[source].addEdge(destination, range);
}
graph::graph(const char* p){
  int n,source=0,destination,range;
  ifstream f(p);
  istream_iterator<int> start(f),end;
  vector<int> numbers(start,end);
  n=numbers[0];
  cursor = 0;
  head = new vertice[n];
  while (cursor < n) {
    head[cursor].set(cursor);
    cursor++;
  }
  cursor = 0;
  size = n;
  vector<int>::iterator it = numbers.begin();
  it++;
  for( ; it != numbers.end(); ++it){
    source=*it;
    it++;
    destination=*it;
    it++;
    range=*it;
    addEdge(source,destination,range);
  }
}
graph::~graph() {
  delete head;
}

int mST(graph & g){
  priorityQue openSet, closedSet;
  priorityQueElement * pQE;
  edgeElement * edge;
  int now = 0, next, range = 0,size,cumulative=0;
  size=g.getsize();
  while(now<size){
    while (edge = g.getVertice(now) -> popEdge()) {
      openSet.pushPQ(edge -> destination,now, edge -> range);
    }
    now++;
  }
  while(pQE=openSet.popPQ()){
    if(openSet.isInclude(pQE->id)){
      continue;
    }else{
      closedSet.pushPQ(pQE->id,pQE->source,pQE->priority);
    }
    cout<<closedSet;
    while(pQE=closedSet.popPQ()){
      cumulative+=pQE->priority;
    }
  }
  return cumulative;
}
int main() {
  graph g("a.txt");
  cout <<mST(g);
  return 0;
}
