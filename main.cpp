#include <iostream>
#include <list>

using namespace std;

class Vertex {
public:
  bool explored;
  int id;
  list<Vertex *> path;

  Vertex(int id) {
    explored = false;
    this->id = id;
  }
};

class Edge {
public:
  Vertex *A;
  Vertex *B;

  int weight;
  Edge(int weight) { this->weight = weight; }
};

list<Edge *> getEdges(Vertex *v, list<Edge *> edges) {
  list<Edge *> out;

  for (Edge *edge : edges) {
    if (edge->A->id == v->id || edge->B->id == v->id) {
      out.push_back(edge);
    }
  }

  return out;
}

int main() {

  list<Vertex *> vertices;
  list<Edge *> edges;

  int n_bases, n_pipes;
  cin >> n_bases >> n_pipes;
  cout << "n_bases: " << n_bases << " n_pipes: " << n_pipes << endl;

  int startinNode, targetNode;
  cin >> startinNode >> targetNode;
  cout << "startinNode: " << startinNode << " targetNode: " << targetNode
       << endl;

  int totalTime;
  cin >> totalTime;
  cout << "totalTime: " << totalTime << endl;

  for (int i = 0; i < n_pipes; i++) {
    int a, b, weight;
    cin >> a >> b >> weight;

    Vertex *nodeA = nullptr;
    Vertex *nodeB = nullptr;
    for (Vertex *v : vertices) {
      if (v->id == a) {
        nodeA = v;
      }
      if (v->id == b) {
        nodeB = v;
      }
    }
    if (nodeA == nullptr) {
      nodeA = new Vertex(a);
      vertices.push_back(nodeA);
    }
    if (nodeB == nullptr) {
      nodeB = new Vertex(b);
      vertices.push_back(nodeB);
    }

    Edge *edge = new Edge(weight);
    edge->A = nodeA;
    edge->B = nodeB;
    edges.push_front(edge);
  }
  // print all nodes

  for (Vertex *v : vertices) {
    cout << v->id << ": ";
    list<Edge *> vertexEdges = getEdges(v, edges);

    for (Edge *e : vertexEdges) {
      cout << "(" << e->A->id << ", " << e->B->id << ")";
    }
    cout << endl;
  }
}
