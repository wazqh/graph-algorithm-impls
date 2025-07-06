#ifndef K_CORE_COMMON_H
#define K_CORE_COMMON_H

#include <bits/stdc++.h>
using namespace std;

class Graph {
private:
    unordered_map<int, unordered_set<int>> adj;  // adjacency list
    unordered_map<int, int> degrees;             // current degrees
    set<pair<int, int>> min_degree_set;          // (degree, node) for fast min degree lookup
    unordered_set<int> deleted;                  // mark deleted nodes

public:
    void addEdge(int u, int v) {
        if (adj[u].insert(v).second) degrees[u]++;
        if (adj[v].insert(u).second) degrees[v]++;
        min_degree_set.insert({degrees[u], u});
        min_degree_set.insert({degrees[v], v});
    }

    void readFromFile(const string& filename) {
        ifstream infile(filename);
        if (!infile) {
            cerr << "Error opening file: " << filename << endl;
            return;
        }
        int u, v;
        while (infile >> u >> v) {
            addEdge(u, v);
        }
        infile.close();
    }

    void buildMinDegreeSet() {
        min_degree_set.clear();
        for (auto& [u, deg] : degrees) {
            if (deleted.count(u)) continue;
            min_degree_set.insert({deg, u});
        }
    }

    void removeMinDegreeVertex() {
        if (min_degree_set.empty()) return;
        auto [deg, u] = *min_degree_set.begin();
        min_degree_set.erase(min_degree_set.begin());
        deleted.insert(u);

        for (int v : adj[u]) {
            if (deleted.count(v)) continue;
            min_degree_set.erase({degrees[v], v});
            adj[v].erase(u);
            degrees[v]--;
            min_degree_set.insert({degrees[v], v});
        }
        adj[u].clear();
        degrees[u] = 0;
    }

    bool isConnected(const unordered_set<int>& subset) {
        if (subset.empty()) return true;
        queue<int> q;
        unordered_set<int> visited;

        int start = *subset.begin();
        q.push(start);
        visited.insert(start);

        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int v : adj[u]) {
                if (deleted.count(v) || !subset.count(v) || visited.count(v)) continue;
                visited.insert(v);
                q.push(v);
            }
        }

        return visited.size() == subset.size();
    }

    int goodness(const unordered_set<int>& subset) {
        int minDeg = INT_MAX;
        for (int v : subset) {
            if (deleted.count(v)) continue;
            int cnt = 0;
            for (int nei : adj[v]) {
                if (subset.count(nei)) cnt++;
            }
            minDeg = min(minDeg, cnt);
        }
        return minDeg;
    }

    unordered_set<int> getConnectedComponentIncluding(const unordered_set<int>& query) {
        unordered_set<int> component;
        if (query.empty()) return component;
        int start = *query.begin();
        queue<int> q;
        q.push(start);
        component.insert(start);

        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int v : adj[u]) {
                if (deleted.count(v) || component.count(v)) continue;
                component.insert(v);
                q.push(v);
            }
        }
        for (int qv : query) {
            if (!component.count(qv)) return {};  // not fully connected
        }
        return component;
    }

    unordered_set<int> globalSearch(const unordered_set<int>& query) {
        vector<unordered_set<int>> snapshots;
        vector<int> snapshot_goodness;

        while (true) {
            unordered_set<int> component = getConnectedComponentIncluding(query);
            if (component.empty()) break;
            snapshots.push_back(component);
            snapshot_goodness.push_back(goodness(component));

            buildMinDegreeSet();
            if (!min_degree_set.empty() && query.count(min_degree_set.begin()->second)) break;
            removeMinDegreeVertex();
        }

        int maxIdx = max_element(snapshot_goodness.begin(), snapshot_goodness.end()) - snapshot_goodness.begin();
        return snapshots[maxIdx];
    }

    unordered_set<int> localSearch(int queryVertex, int maxSteps = 100) {
        unordered_set<int> candidateSet = {queryVertex};
        set<pair<int, int>> frontier; // (connection count, vertex)
        unordered_set<int> visited = {queryVertex};

        for (int v : adj[queryVertex]) {
            frontier.insert({1, v});
            visited.insert(v);
        }

        for (int step = 0; step < maxSteps && !frontier.empty(); ++step) {
            auto it = --frontier.end();
            int v = it->second;
            frontier.erase(it);
            candidateSet.insert(v);

            for (int u : adj[v]) {
                if (visited.count(u)) continue;
                int conn = 0;
                for (int w : adj[u]) {
                    if (candidateSet.count(w)) conn++;
                }
                frontier.insert({conn, u});
                visited.insert(u);
            }
        }

        // extract largest connected component containing queryVertex
        queue<int> q;
        q.push(queryVertex);
        unordered_set<int> visitedComp = {queryVertex};
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int v : adj[u]) {
                if (!candidateSet.count(v) || visitedComp.count(v)) continue;
                visitedComp.insert(v);
                q.push(v);
            }
        }
        return visitedComp;
    }

    unordered_set<int> indexBasedSearch(const unordered_set<int>& query) {
        unordered_map<int, int> core;
        unordered_map<int, unordered_set<int>> levelShell;

        // k-core decomposition
        auto cmp = [&](int a, int b) { return degrees[a] > degrees[b]; };
        priority_queue<int, vector<int>, decltype(cmp)> pq(cmp);
        unordered_map<int, bool> removed;
        for (auto& [v, _] : adj) pq.push(v);

        while (!pq.empty()) {
            int v = pq.top(); pq.pop();
            if (removed[v]) continue;
            removed[v] = true;
            core[v] = degrees[v];
            levelShell[core[v]].insert(v);
            for (int u : adj[v]) {
                if (!removed[u]) {
                    degrees[u]--;
                    pq.push(u);
                }
            }
        }

        int maxL = INT_MIN;
        for (int q : query) maxL = max(maxL, core[q]);

        for (int l = maxL; l >= 0; --l) {
            unordered_set<int> subgraph;
            for (int v : levelShell[l]) subgraph.insert(v);

            unordered_set<int> component = getConnectedComponentIncluding(query);
            if (!component.empty()) return component;
        }
        return {};
    }
};


class DirectedGraph {
private:
    unordered_map<int, unordered_set<int>> outAdj;  // adjacency list (outgoing)
    unordered_map<int, unordered_set<int>> inAdj;   // adjacency list (incoming)
    unordered_map<int, int> inDegrees;
    unordered_map<int, int> outDegrees;

public:
    void addEdge(int u, int v) {
        if (outAdj[u].insert(v).second) outDegrees[u]++;
        if (inAdj[v].insert(u).second) inDegrees[v]++;
    }

    void readFromFile(const string& filename) {
        ifstream infile(filename);
        if (!infile) {
            cerr << "Error opening file: " << filename << endl;
            return;
        }
        int u, v;
        while (infile >> u >> v) {
            addEdge(u, v);
        }
        infile.close();
    }

    unordered_set<int> peel(int k, int l) {
        queue<int> q;
        unordered_set<int> valid;

        for (auto& [v, _] : outAdj) valid.insert(v);

        for (auto& v : valid) {
            if (inDegrees[v] < k || outDegrees[v] < l) q.push(v);
        }

        unordered_set<int> removed;

        while (!q.empty()) {
            int u = q.front(); q.pop();
            if (!valid.count(u)) continue;
            valid.erase(u);
            removed.insert(u);

            for (int v : outAdj[u]) {
                if (!valid.count(v)) continue;
                inDegrees[v]--;
                if (inDegrees[v] < k || outDegrees[v] < l) q.push(v);
            }
            for (int v : inAdj[u]) {
                if (!valid.count(v)) continue;
                outDegrees[v]--;
                if (inDegrees[v] < k || outDegrees[v] < l) q.push(v);
            }
        }

        return valid;
    }

    unordered_set<int> klCoreSecondMethod(int k, int l) {
        unordered_set<int> core_k_l = peel(k, l);
        unordered_set<int> core_k1_l = peel(k + 1, l);
        unordered_set<int> core_k_l1 = peel(k, l + 1);

        unordered_set<int> result;

        if (core_k1_l.size() >= core_k_l1.size()) {
            for (int v : core_k_l) {
                if (!core_k1_l.count(v)) result.insert(v);
            }
        } else {
            for (int v : core_k_l) {
                if (!core_k_l1.count(v)) result.insert(v);
            }
        }
        return result;
    }

    unordered_set<int> connectedComponentContaining(int q, const unordered_set<int>& subgraph) {
        unordered_set<int> visited;
        queue<int> que;
        if (!subgraph.count(q)) return {};
        que.push(q);
        visited.insert(q);

        while (!que.empty()) {
            int u = que.front(); que.pop();
            for (int v : outAdj[u]) {
                if (subgraph.count(v) && !visited.count(v)) {
                    visited.insert(v);
                    que.push(v);
                }
            }
            for (int v : inAdj[u]) {
                if (subgraph.count(v) && !visited.count(v)) {
                    visited.insert(v);
                    que.push(v);
                }
            }
        }
        return visited;
    }
};


#endif //K_CORE_COMMON_H


