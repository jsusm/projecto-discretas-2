#include <climits>
#include <iostream>
#include <list>

using namespace std;

class Vertex {
public:
  bool explored;
  int id;
  int minTime;
  list<Vertex *> path;

  Vertex(int id) {
    explored = false;
    this->id = id;
    minTime = INT_MAX;
  }

  void print() {
    cout << (explored ? "T" : "F") << " " << id << " {time: " << minTime
         << ", path: [";
    for (Vertex *v : path) {
      cout << v->id << ", ";
    }
    cout << "]}" << endl;
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

/** Retorna el nodo objetivo, ciertos nodos se marcan como explorados,
 * esos nodos tienen el camino minimos desde el nodo de partida
 * al nodo objetivo, si no se encuentra un camino entre el nodo
 * de partida y el nodo objetivo, retorna el ultimo vertice explorado
 */
Vertex* dijkstra(list<Edge *> edges, list<Vertex *> vertices, int startingNodeId,
             int targetNodeId) {
  Vertex *starting;
  Vertex *target;
  // buscamos el nodo de inicio y del final
  for (Vertex *v : vertices) {
    if (v->id == startingNodeId) {
      starting = v;
    }
    if (v->id == targetNodeId) {
      target = v;
    }
  }

  starting->minTime = 0;
  starting->explored = true;

  Vertex *currVertex = starting;
  while (currVertex->id != targetNodeId) {
    list<Edge *> vertexEdges = getEdges(currVertex, edges);
    // Actualizamos los tiempos minimos
    for (Edge *e : vertexEdges) {
      Vertex *connectionVertex = e->A->id == currVertex->id ? e->B : e->A;

      if (currVertex->minTime + e->weight < connectionVertex->minTime) {
        connectionVertex->minTime = currVertex->minTime + e->weight;
        // copy path
        connectionVertex->path.clear();
        for(Vertex* v: currVertex->path) {
          connectionVertex->path.push_back(v);
        }
        connectionVertex->path.push_back(currVertex);
      }
    }
    // Buscamos el vertice que tenga menor tiempor y lo exploramos
    Vertex *minVertex = nullptr;
    for (Vertex *v : vertices) {
      if (v->explored)
        continue;
      if (minVertex == nullptr) {
        minVertex = v;
      }
      if (v->minTime < minVertex->minTime) {
        minVertex = v;
      }
    }
    // todos los nodos estan explorados
    if(minVertex==nullptr) {
      return currVertex;
    }
    minVertex->explored = true;
    currVertex = minVertex;
    currVertex->print();
  }

  currVertex->print();
  return currVertex;
}

void cleanEdges(list<Edge *> &edges, Vertex* v) {
  // iteramos sobrelas edges
  Vertex* currVertex = v;
  while(currVertex->minTime != 0){
    // Buscamos la arista que connecta con este nodo
    list<Edge*>::iterator linkEdge;
    for(list<Edge*>::iterator it= edges.begin(); it != edges.end();) {
      Edge* e = *it;
      Vertex *connectionVertex = e->A->id == currVertex->id ? e->B : e->A;
      if(connectionVertex->id == currVertex->path.back()->id) {
        linkEdge = it;
        currVertex = connectionVertex;
        connectionVertex->print();
        break;
      }
      ++it;
    }
    // la borramos
    edges.erase(linkEdge);
  }
}

int main() {
  /// Entrada
  list<Vertex *> vertices;
  list<Edge *> edges;

  int n_bases, n_pipes;
  cin >> n_bases >> n_pipes;
  cout << "n_bases: " << n_bases << " n_pipes: " << n_pipes << endl;

  int startingNode, targetNode;
  cin >> targetNode >> startingNode;
  cout << "startinNode: " << startingNode << " targetNode: " << targetNode
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
      // asignamos si exsisten
      if (v->id == a) {
        nodeA = v;
      }
      if (v->id == b) {
        nodeB = v;
      }
    }
    // si no existen los creamos
    if (nodeA == nullptr) {
      nodeA = new Vertex(a);
      vertices.push_back(nodeA);
    }
    if (nodeB == nullptr) {
      nodeB = new Vertex(b);
      vertices.push_back(nodeB);
    }
    // aniadimos la arista
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

  Vertex* targetVertex = dijkstra(edges, vertices, startingNode, targetNode);
  int time1 = targetVertex->minTime;
  if(time1 > totalTime) {
    cout << "Bowser se lleva a la princesa" << endl;
    return 0;
  }

  // limpiamos las aristas usadas
  cleanEdges(edges, targetVertex);
  // limpiamos los nodos
  for(Vertex* v: vertices) {
    v->explored = false;
    v->minTime = INT_MAX;
    v->path.clear();
    v->print();
  }


  Vertex* homeVertex = dijkstra(edges, vertices, targetNode, startingNode);
  int time2 = homeVertex->minTime;
  if(homeVertex->id != startingNode || time2 + time1 > totalTime) {
    // No se encontro un camino de vuelta
    cout << "Bowser te atrapa con la princesa" << endl;
    return 0;
  }
  cout << "La princesa es salvada" << endl;
  return 0;
}
