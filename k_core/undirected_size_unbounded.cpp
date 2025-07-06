#include "common.h"

/* local
 * 1.  let $G_0 = G$ and $G_t$ be the graphs in $t-th$ iterations($1\leq t \leq n$)
 * 2.  remove the vertex which has the minimum degree in $G_{t-1}$ and obtain an updated graph.txt $G_t$
 * 3.  repeat step ii until at least one of the query vertices $Q$ has minimum in the graph.txt $G_{T-1}$ or the query vertices $Q$ are no longer connected.
 * 4.  let $G_{t}^{'}$ be the connected component containing $Q$ in $G_t$. Then the subgraph $G_{O}= arg\space max\{f(G^{'}_t)\}$
 */


int main() {
    Graph g;
    g.readFromFile("../graph.txt");

    unordered_set<int> query = {1, 2};
    auto global = g.globalSearch(query);
    cout << "Global Search Result: ";
    for (int v : global) cout << v << " ";
    cout << endl;

    auto local = g.localSearch(1);
    cout << "Local Search Result: ";
    for (int v : local) cout << v << " ";
    cout << endl;

    auto index = g.indexBasedSearch(query);
    cout << "Index-Based Search Result: ";
    for (int v : index) cout << v << " ";
    cout << endl;

    return 0;
}
