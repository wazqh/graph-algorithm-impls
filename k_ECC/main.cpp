#include "bits/stdc++.h"

using namespace std;

struct Edge {
    int u, v;
    int weight; // connectivity value
    bool operator<(const Edge& other) const {
        return weight > other.weight; // for max spanning tree
    }
};


// a unionFind to generate the maximum spanning tree
class UnionFind {
    vector<int> parent, rank;
public:
    UnionFind(int n) {
        parent.resize(n);
        rank.assign(n, 0);
        for (int i = 0; i < n; i++) parent[i] = i;
    }
    int find(int x) {
        if (parent[x] != x)
            parent[x] = find(parent[x]);
        return parent[x];
    }
    bool unite(int x, int y) {
        int xr = find(x), yr = find(y);
        if (xr == yr) return false;
        if (rank[xr] < rank[yr])
            parent[xr] = yr;
        else if (rank[xr] > rank[yr])
            parent[yr] = xr;
        else {
            parent[yr] = xr;
            rank[xr]++;
        }
        return true;
    }
};


vector<Edge> computeEfficientSMCS(int n, const vector<Edge>& edges, const set<int>& Q) {
    // Step 1: Sort edges for Kruskal's algorithm
    vector<Edge> sortedEdges = edges;
    sort(sortedEdges.begin(), sortedEdges.end());

    // Step 2: Kruskal to get maximum spanning tree (MST)
    UnionFind uf(n);
    vector<Edge> mst;
    for (const auto& e : sortedEdges) {
        if (uf.unite(e.u, e.v)) {
            mst.push_back(e);
        }
    }

    // Step 3: Find λ(H) — the minimum edge weight along paths connecting all Q
    // We'll build a tree from MST and perform DFS to find λ(H)
    unordered_map<int, vector<pair<int, int>>> tree;
    for (const auto& e : mst) {
        tree[e.u].emplace_back(e.v, e.weight);
        tree[e.v].emplace_back(e.u, e.weight);
    }

    // λ(H) is defined as the minimum edge weight on the Steiner tree connecting Q
    // For simplicity, we’ll perform DFS from each query vertex and track minimum edge weight
    // Final λ(H) = min weight on all paths connecting Q (simplified method)
    set<pair<int, int>> visitedPairs;
    int lambdaH = INT_MAX;

    function<void(int, int, int, set<int>&)> dfs = [&](int u, int prev, int minWeight, set<int>& visited) {
        visited.insert(u);
        for (auto [v, w] : tree[u]) {
            if (v == prev) continue;
            lambdaH = min(lambdaH, w);
            dfs(v, u, min(minWeight, w), visited);
        }
    };

    // Do DFS from any query vertex, explore reachable Q nodes
    auto it = Q.begin();
    set<int> visited;
    dfs(*it, -1, INT_MAX, visited);

    // Step 4: Extract subtree with edge weight ≥ λ(H)
    vector<Edge> result;
    for (const auto& e : mst) {
        if (e.weight >= lambdaH) {
            result.push_back(e);
        }
    }
    return result;
}
