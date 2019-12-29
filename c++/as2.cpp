#include <iostream>

#include <cstdlib>

#include <ctime>

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
  graph(int n, double density, int maxRange, int minRange);
  void addEdge(int source, int destination, int range);
  vertice * getVertice(int id) {
    return &(head[id]);
  }~graph();
};

struct priorityQueElement {
  int id;
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
  void pushPQ(int id, int priority);
  int isShorter(int id, int priority);
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
void priorityQue::pushPQ(int id, int priority) {
  //pushes element to priority que with given id and priority(range)
  priorityQueElement * elementP, * temp;
  cursor = head;
  elementP = new priorityQueElement;
  elementP -> id = id;
  elementP -> priority = priority;
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
int priorityQue::isShorter(int id, int priority) {
  //returns if given element is the shortest, exist or not
  // in this function 2 means no element in queue
  cursor = head;
  while (cursor != NULL) {
    if (cursor -> id == id) {
      return (id < cursor -> id);
    } else {
      cursor = cursor -> next;
    }
  }
  return 2;
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
graph::~graph() {
  delete head;
}
int findShortestPath(graph & g, int source, int destination) {
  priorityQue openSet, closedSet;
  priorityQueElement * pQE;
  edgeElement * edge;
  int now = source, next, range = 0;
  while (now != destination) {
    closedSet.pushPQ(now, range);
    while (edge = g.getVertice(now) -> popEdge()) {
      if (closedSet.isShorter(edge -> destination, edge -> range + range) != 2) {
        continue;
      } else;
      switch (openSet.isShorter(edge -> destination, edge -> range + range)) {
      case 2:
        {
          openSet.pushPQ(edge -> destination, edge -> range + range);
          break;
        }
      case 1:
        {
          openSet.changePriority(edge -> destination, edge -> range + range);
          break;
        }
      default:
        {

        }
      }
    }
    g.getVertice(now) -> init();
    pQE = openSet.popPQ();
    if (pQE == NULL) {
      cout << "no way to " << destination << endl;
      return 0;
    }
    now = pQE -> id;
    range = pQE -> priority;
    delete pQE;
  }
  return range;
}
int main() {
  srand(clock());
  int cumulative1 = 0, cumulative2 = 0, n = 1;
  graph g1(50, 0.2, 1, 10);
  graph g2(50, 0.4, 1, 10);
  while (n < 50) {
    cumulative1 += findShortestPath(g1, 0, n);
    cumulative2 += findShortestPath(g2, 0, n);
    n++;
  }
  cout << " what i learned in this assignment: \n ";
  cout << "firstly it was not so easy  for me i was new with object oriented programming  paradigm and i started 2 week late this course.\n";
  cout <<" It made me hurry and i tried to be as fast as possible in order to reach deadlines  however i could not do that.\n";
  cout<<"After that in this assigment i have learned how c++can mix functions and variables in objects and what is  its ' difficulties.\n";
  cout<<"My functions had side effects and i tried do solve them.\n";
  cout<<"Graph is also new for me because i am a 1st year student we haven't taken data structures lecture yet\n";
  cout<< "Therefore it was my first meet with graph i think it is so useful and with this in real life example it is more understandable.\n";
  cout<<"i tried to find a ide  for me but i could not set it up therefore i used gdb and it make debugging hard but helpful.\n";
  cout <<"Constructor and deconstructor concepts are very interesting and useful"<< endl;
  cout << "average of 0.2 density" << cumulative1 / (double) n << endl;
  cout << "average of 0.4 density" << cumulative2 / (double) n << endl;

  return 0;
}
