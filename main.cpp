#include <iostream>
#include <list>

using namespace std;

class Vertex {
public:
  bool explored;
  int id;
  list<Vertex *> path;
};

class Edge {
public:
  Vertex* A;
  Vertex* B;

  int weight;
};

list<Edge*> getEdges(Vertex* v, list<Edge*> edges) {
  list<Edge*> out;

  for(Edge* edge: edges) {
    if(edge->A->id == v->id || edge->B->id == v->id) {
      out.push_back(edge);
    }
  }

  return out;
}

void entrada() {
  int n_bases, n_pipes;
  cin >> n_bases >> n_pipes;
  cout << "n_bases: " << n_bases<< " n_pipes: " << n_pipes<< endl;

  int startinNode, targetNode;
  cin >> startinNode >> targetNode;
  cout<< "startinNode: " << startinNode<< " targetNode: " << targetNode << endl;

  int totalTime;
  cin >> totalTime;
  cout << "totalTime: " << totalTime << endl;
}

int main(){
  entrada();
}
