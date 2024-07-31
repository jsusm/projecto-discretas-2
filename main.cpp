#include <iostream>

using namespace std;

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
