#include "common.h"

int main() {
    DirectedGraph g;
    g.readFromFile("graph.txt");

    int q = 1;
    int k = 1, l = 1;
    unordered_set<int> result = g.klCoreSecondMethod(k, l);

    cout << "Vertices in (" << k << "," << l << ")-core: ";
    for (int v : result) cout << v << " ";
    cout << endl;

    unordered_set<int> component = g.connectedComponentContaining(q, result);
    cout << "Connected Component containing " << q << ": ";
    for (int v : component) cout << v << " ";
    cout << endl;

    if (component.count(q)) {
        cout << "Query vertex " << q << " is included in the final connected subgraph." << endl;
    } else {
        cout << "Query vertex " << q << " is NOT included in the final connected subgraph." << endl;
    }

    return 0;
}
