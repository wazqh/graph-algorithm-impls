//
// Created by HQ142 on 2025/7/7.
//

#ifndef K_CLIQUE_COMMON_H
#define K_CLIQUE_COMMON_H
#include <bits/stdc++.h>

using namespace std;

class Graph {
private:
    int n; // 顶点个数
     vector< vector<int>> adj; // 邻接表

    const  vector<int>& neighbors(int u) const {
        return adj[u];
    }
public:
    Graph(int n) : n(n), adj(n) {}

    void add_edge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // 判断是否是 γ-quasi-k-clique
    bool is_gamma_quasi_clique(const  vector<int>& clique, const Graph& G, double gamma) {
        int k = clique.size();
        int min_degree =  ceil(gamma * (k - 1));
        for (int u : clique) {
            int count = 0;
            for (int v : clique) {
                if (u != v &&  find(G.adj[u].begin(), G.adj[u].end(), v) != G.adj[u].end())
                    ++count;
            }
            if (count < min_degree)
                return false;
        }
        return true;
    }

    // 判断两个 clique 是否 α-adjacent
    bool is_alpha_adjacent(const  vector<int>& c1, const  vector<int>& c2, int alpha) {
        int common = 0;
        for (int v1 : c1) {
            if ( find(c2.begin(), c2.end(), v1) != c2.end()) {
                ++common;
            }
        }
        return common >= alpha;
    }

    // Bron-Kerbosch 枚举 γ-quasi-k-clique
    void bron_kerbosch( vector<int>& R,  vector<int>& P,  vector<int>& X,
                       const Graph& G,  vector< vector<int>>& cliques, int k, double gamma, int q) {
        if (R.size() == k) {
            if ( find(R.begin(), R.end(), q) != R.end() && is_gamma_quasi_clique(R, G, gamma)) {
                cliques.push_back(R);
            }
            return;
        }

        if (P.empty()) return;

         vector<int> P_copy = P;
        for (int v : P_copy) {
             vector<int> R_new = R;
            R_new.push_back(v);

             vector<int> P_new, X_new;
            for (int u : G.neighbors(v)) {
                if ( find(P.begin(), P.end(), u) != P.end())
                    P_new.push_back(u);
                if ( find(X.begin(), X.end(), u) != X.end())
                    X_new.push_back(u);
            }

            bron_kerbosch(R_new, P_new, X_new, G, cliques, k, gamma, q);

            P.erase( remove(P.begin(), P.end(), v), P.end());
            X.push_back(v);
        }
    }

    // 构建 clique adjacency graph 并返回包含查询点的组件
     vector<int> get_component_with_query(const  vector< vector<int>>& cliques, int alpha, int query_idx) {
        int n = cliques.size();
         vector< vector<int>> clique_graph(n);

        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                if (is_alpha_adjacent(cliques[i], cliques[j], alpha)) {
                    clique_graph[i].push_back(j);
                    clique_graph[j].push_back(i);
                }
            }
        }

         vector<bool> visited(n, false);
         vector<int> result;
         queue<int> q;
        q.push(query_idx);
        visited[query_idx] = true;

        while (!q.empty()) {
            int u = q.front(); q.pop();
            result.push_back(u);
            for (int v : clique_graph[u]) {
                if (!visited[v]) {
                    visited[v] = true;
                    q.push(v);
                }
            }
        }
        return result;
    }

    // 主流程
    void alpha_gamma_ocs(const Graph& G, int k, double gamma, int alpha, int q) {
         vector<int> R, P, X;
        for (int i = 0; i < G.n; ++i) P.push_back(i);

         vector< vector<int>> cliques;
        bron_kerbosch(R, P, X, G, cliques, k, gamma, q);

        int query_idx = -1;
        for (int i = 0; i < cliques.size(); ++i) {
            if ( find(cliques[i].begin(), cliques[i].end(), q) != cliques[i].end()) {
                query_idx = i;
                break;
            }
        }

        if (query_idx == -1) {
             cout << "No valid clique found containing query point." <<  endl;
            return;
        }

         vector<int> component = get_component_with_query(cliques, alpha, query_idx);

         cout << "Found component with " << component.size() << " cliques containing query " << q << ":\n";
        for (int idx : component) {
            for (int v : cliques[idx])
                 cout << v << " ";
             cout <<  endl;
        }
    }


    using Clique = set<int>;

    // 比较两个clique是否共享k-1个节点
    bool isKMinus1Adjacent(const Clique& c1, const Clique& c2, int k) {
        int count = 0;
        for (int v : c1) {
            if (c2.count(v)) count++;
        }
        return count >= k - 1;
    }

    // 使用 Bron-Kerbosch + pivot 枚举所有 k-cliques
    void bronKerbosch(vector<Clique>& cliques, Clique R, set<int> P, set<int> X, const Graph& G, int k) {
        if (R.size() == k) {
            cliques.push_back(R);
            return;
        }
        if (P.empty() && X.empty()) return;

        int u = *P.begin(); // pivot
        set<int> P_without_neighbors;
        for (int v : P) {
            if (!count(G.neighbors(u).begin(), G.neighbors(u).end(), v)) {
                P_without_neighbors.insert(v);
            }
        }

        for (int v : P_without_neighbors) {
            Clique R_new = R;
            R_new.insert(v);

            set<int> P_new, X_new;
            for (int u2 : G.neighbors(v)) {
                if (P.count(u2)) P_new.insert(u2);
                if (X.count(u2)) X_new.insert(u2);
            }
            bronKerbosch(cliques, R_new, P_new, X_new, G, k);
            P.erase(v);
            X.insert(v);
        }
    }

    // 构建 k-clique percolation 图（每个点是一个 clique）
    vector<vector<int>> buildCliqueGraph(const vector<Clique>& cliques, int k) {
        int m = cliques.size();
        vector<vector<int>> cliqueAdj(m);
        for (int i = 0; i < m; ++i) {
            for (int j = i + 1; j < m; ++j) {
                if (isKMinus1Adjacent(cliques[i], cliques[j], k)) {
                    cliqueAdj[i].push_back(j);
                    cliqueAdj[j].push_back(i);
                }
            }
        }
        return cliqueAdj;
    }

    // BFS查找联通分量
    vector<vector<int>> findComponents(const vector<vector<int>>& cliqueGraph) {
        int n = cliqueGraph.size();
        vector<bool> visited(n, false);
        vector<vector<int>> components;

        for (int i = 0; i < n; ++i) {
            if (!visited[i]) {
                vector<int> comp;
                vector<int> stack = {i};
                visited[i] = true;

                while (!stack.empty()) {
                    int u = stack.back(); stack.pop_back();
                    comp.push_back(u);
                    for (int v : cliqueGraph[u]) {
                        if (!visited[v]) {
                            visited[v] = true;
                            stack.push_back(v);
                        }
                    }
                }
                components.push_back(comp);
            }
        }
        return components;
    }

// 主函数：查找包含查询点q的最密集 clique percolation community
    vector<int> findDCPC(const Graph& G, int queryVertex) {
        int maxK = 0;

        // 找到图中最大度数作为 k 的上限
        for (int i = 0; i < G.n; ++i) {
            maxK = max(maxK, (int)G.neighbors(i).size() + 1);
        }

        for (int k = maxK; k >= 2; --k) {
            // 枚举所有 k-cliques
            vector<Clique> cliques;
            set<int> allVertices;
            for (int i = 0; i < G.n; ++i) allVertices.insert(i);
            bronKerbosch(cliques, {}, allVertices, {}, G, k);

            if (cliques.empty()) continue;

            // 构建 k-clique percolation 图
            vector<vector<int>> cliqueGraph = buildCliqueGraph(cliques, k);

            // 找到包含查询点的 clique component
            vector<vector<int>> components = findComponents(cliqueGraph);
            for (const auto& comp : components) {
                for (int cliqueID : comp) {
                    if (cliques[cliqueID].count(queryVertex)) {
                        // 返回此 component 所有节点（合并 clique 中所有点）
                        set<int> result;
                        for (int cid : comp) {
                            result.insert(cliques[cid].begin(), cliques[cid].end());
                        }
                        return vector<int>(result.begin(), result.end());
                    }
                }
            }
        }

        // 如果没有找到
        return {};
    }
};





#endif //K_CLIQUE_COMMON_H
