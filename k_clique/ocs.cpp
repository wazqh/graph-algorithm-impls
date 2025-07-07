#include "common.h"

// 示例使用
int main() {
    Graph G(6);
    G.add_edge(0, 1);
    G.add_edge(0, 2);
    G.add_edge(1, 2);
    G.add_edge(1, 3);
    G.add_edge(2, 3);
    G.add_edge(3, 4);
    G.add_edge(4, 5);
    G.add_edge(3, 5);

    int k = 3;
    double gamma = 0.6;
    int alpha = 2;
    int query = 1;

    G.alpha_gamma_ocs(G, k, gamma, alpha, query);
    return 0;
}
