//
// Created by HQ142 on 2025/7/6.
//

#ifndef K_TRUSS_COMMON_H
#define K_TRUSS_COMMON_H

#include <bits/stdc++.h>

using namespace std;

// ----------- Online k-Truss Community Search -------------
// 用结构体表示无向边，确保 u < v 用于哈希和比较：
struct Edge {
    int u, v;
    Edge(int a, int b) : u(min(a, b)), v(max(a, b)) {}
    bool operator==(const Edge& o) const { return u == o.u && v == o.v; }
};
struct EdgeHash {
    size_t operator()(const Edge& e) const {
        return hash<long long>()(((long long)e.u << 32) | (unsigned)e.v);
    }
};

// 图结构，包含邻接表和每条边的 truss number
class Graph {
public:
    int n;
    vector<vector<int>> adj;
    unordered_map<Edge, int, EdgeHash> trussness;

    Graph(int nodes): n(nodes), adj(nodes) {}
    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // 假设已实现 truss decomposition，填充 trussness
    void computeTrussness();

    vector< set<Edge> > queryKTrussCommunity(int q, int k);
};

vector< set<Edge> > Graph::queryKTrussCommunity(int q, int k) {
    unordered_set<long long> visitedE;
    vector< set<Edge> > communities;

    for (int nei : adj[q]) {
        Edge start(q, nei);
        if (trussness[start] < k ||
            visitedE.count(((long long)start.u << 32) | start.v))
            continue;

        queue<Edge> bfs;
        set<Edge> com;
        bfs.push(start);

        while (!bfs.empty()) {
            Edge e = bfs.front(); bfs.pop();
            long long key = ((long long)e.u << 32) | e.v;
            if (visitedE.count(key)) continue;

            visitedE.insert(key);
            com.insert(e);

            // 扩展相互三角……
            for (int w : adj[e.u]) {
                if (w == e.v) continue;
                if (!binary_search(adj[e.v].begin(), adj[e.v].end(), w)) continue;
                Edge e1(e.u, w), e2(e.v, w);
                if (trussness[e1] >= k) bfs.push(e1);
                if (trussness[e2] >= k) bfs.push(e2);
            }
        }
        communities.push_back(com);
    }
    return communities;
}

// ----------- TCP-Index Based Search -------------
struct WeightedEdge {
    int u, v, w;
    bool operator<(const WeightedEdge& o) const { return w > o.w; }
};

class TCPIndex {
public:
    unordered_map<int, vector<WeightedEdge>> idx;

    void build(Graph& G) {
        for (int x = 0; x < G.n; ++x) {
            auto &nbrs = G.adj[x];
            // 构造邻域图并收集加权边
            for (int i = 0; i < nbrs.size(); ++i)
                for (int j = i+1; j < nbrs.size(); ++j) {
                    int y = nbrs[i], z = nbrs[j];
                    if (binary_search(G.adj[y].begin(), G.adj[y].end(), z)) {
                        int w = min({ G.trussness[Edge(x,y)],
                                      G.trussness[Edge(x,z)],
                                      G.trussness[Edge(y,z)] });
                        idx[x].push_back({y, z, w});
                    }
                }
            // 可选步骤：用 Kruskal 或 Prim 构造最大生成森林
        }
    }

    set<int> query(Graph& G, int q, int k) {
        set<int> community;
        for (int nei : G.adj[q]) {
            if (G.trussness[Edge(q, nei)] == k) {
                community.insert(nei);
                for (auto &we : idx[q]) {
                    if (we.w >= k) {
                        community.insert(we.u);
                        community.insert(we.v);
                    }
                }
            }
        }
        return community;
    }
};

// ----------- EquiTruss Index Based Search -------------
class EquiTrussIndex {
public:
    unordered_map<Edge, int, EdgeHash> edgeToClass;
    unordered_map<int, set<Edge>> classes;
    unordered_map<int, vector<int>> superAdj;
    unordered_map<int, unordered_set<int>> vertex2Classes;

    void build(Graph& G) {
        int cid = 0;
        unordered_set<Edge, EdgeHash> visited;

        for (auto &pr : G.trussness) {
            const Edge &e0 = pr.first;
            if (visited.count(e0)) continue;
            int k = pr.second;
            deque<Edge> dq;
            dq.push_back(e0);
            visited.insert(e0);
            set<Edge> cls;

            while (!dq.empty()) {
                Edge e = dq.front(); dq.pop_front();
                cls.insert(e);
                for (int w : G.adj[e.u]) {
                    if (w == e.v) continue;
                    if (!binary_search(G.adj[e.v].begin(), G.adj[e.v].end(), w)) continue;
                    for (Edge ne : {Edge(e.u, w), Edge(e.v, w)}) {
                        if (G.trussness[ne] == k && !visited.count(ne)) {
                            visited.insert(ne);
                            dq.push_back(ne);
                        }
                    }
                }
            }

            for (auto &e : cls) {
                edgeToClass[e] = cid;
                classes[cid].insert(e);
                vertex2Classes[e.u].insert(cid);
                vertex2Classes[e.v].insert(cid);
            }
            cid++;
        }

        // 构造超级节点间的连接
        for (auto &pr : classes) {
            int id1 = pr.first;
            for (auto &e : pr.second) {
                for (int w : G.adj[e.u]) {
                    Edge e2(e.v, w);
                    if (edgeToClass.count(e2) && edgeToClass[e2] != id1)
                        superAdj[id1].push_back(edgeToClass[e2]);
                }
            }
        }
    }

    vector< set<Edge> > query(Graph& G, int q, int k) {
        vector<set<Edge>> res;
        unordered_set<int> seenClass;

        for (int cid : vertex2Classes[q]) {
            if (seenClass.count(cid)) continue;
            auto &cls = classes[cid];
            if (cls.empty()) continue;
            Edge sample = *cls.begin();
            if (G.trussness[sample] < k) continue;

            set<int> comp;
            deque<int> dq;
            dq.push_back(cid);

            while (!dq.empty()) {
                int cur = dq.front(); dq.pop_front();
                if (seenClass.count(cur)) continue;
                seenClass.insert(cur);
                comp.insert(cur);
                for (int nxt : superAdj[cur])
                    if (!seenClass.count(nxt)) dq.push_back(nxt);
            }

            set<Edge> community;
            for (int c2 : comp) {
                community.insert(classes[c2].begin(), classes[c2].end());
            }
            res.push_back(community);
        }
        return res;
    }
};





#endif //K_TRUSS_COMMON_H
