#include "common.h"


int main() {
    Graph G(6);
    G. add_edge(0,1); G. add_edge(0,2); G. add_edge(1,2); // triangle
    G. add_edge(2,3); G. add_edge(3,4); G. add_edge(4,5); G. add_edge(5,2); // square with a diagonal

    int queryVertex = 2;
    vector<int> result = G.findDCPC(G, queryVertex);

    cout << "Densest Clique Percolation Community containing node " << queryVertex << ":\n";
    for (int v : result) {
        cout << v << " ";
    }
    cout << endl;

    return 0;
}

