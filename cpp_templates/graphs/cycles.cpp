// Contents
//   directed_cycle    edge ids of some directed cycle in order, empty if the graph is acyclic
//   undirected_cycle  some cycle of an undirected multigraph as {vertices, edge ids}, both empty if it is a forest

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;

// edge ids of some directed cycle, in order (edge i goes u -> v for edges[i] = {u, v}), empty if the graph is acyclic
// iterative DFS: an edge to a vertex still on the DFS stack closes a cycle, O(V + E)
vector<int> directed_cycle(int n, const vector<pair<int, int>> &edges) {
    vector<vector<pair<int, int>>> adj(n);  // {to, edge id}
    for (int i = 0; i < (int)edges.size(); i++) adj[edges[i].first].push_back({edges[i].second, i});
    vector<int> state(n, 0), in_edge(n, -1), next(n, 0);  // state: 0 unseen, 1 on the stack, 2 done
    for (int s = 0; s < n; s++) {
        if (state[s]) continue;
        vector<int> st{s};
        state[s] = 1;
        while (!st.empty()) {
            int u = st.back();
            if (next[u] == (int)adj[u].size()) {
                state[u] = 2;
                st.pop_back();
                continue;
            }
            auto [v, id] = adj[u][next[u]++];
            if (state[v] == 0) {
                state[v] = 1;
                in_edge[v] = id;
                st.push_back(v);
            } else if (state[v] == 1) {  // v -> ... -> u by tree edges, then u -> v
                vector<int> cyc{id};
                for (int x = u; x != v; x = edges[in_edge[x]].first) cyc.push_back(in_edge[x]);
                reverse(cyc.begin(), cyc.end());
                return cyc;
            }
        }
    }
    return {};
}

// some cycle of an undirected multigraph as {vertices v_0..v_{L-1}, edge ids e_0..e_{L-1}}, where e_i joins v_i and
// v_{i+1} (and e_{L-1} joins v_{L-1} and v_0); a self-loop is a cycle of length 1 and two parallel edges one of
// length 2; both empty if the graph is a forest. Iterative DFS that skips only the edge it came in by, O(V + E)
pair<vector<int>, vector<int>> undirected_cycle(int n, const vector<pair<int, int>> &edges) {
    vector<vector<pair<int, int>>> adj(n);  // {to, edge id}
    for (int i = 0; i < (int)edges.size(); i++) {
        auto [u, v] = edges[i];
        adj[u].push_back({v, i});
        if (u != v) adj[v].push_back({u, i});
    }
    vector<int> state(n, 0), par(n, -1), in_edge(n, -1), next(n, 0);
    for (int s = 0; s < n; s++) {
        if (state[s]) continue;
        vector<int> st{s};
        state[s] = 1;
        while (!st.empty()) {
            int u = st.back();
            if (next[u] == (int)adj[u].size()) {
                state[u] = 2;
                st.pop_back();
                continue;
            }
            auto [v, id] = adj[u][next[u]++];
            if (id == in_edge[u]) continue;
            if (state[v] == 0) {
                state[v] = 1;
                par[v] = u;
                in_edge[v] = id;
                st.push_back(v);
            } else if (state[v] == 1) {  // v is an ancestor of u (or u itself): v -> ... -> u by tree edges, then u - v
                vector<int> vs, es;
                for (int x = u; x != v; x = par[x]) {
                    vs.push_back(x);
                    es.push_back(in_edge[x]);
                }
                vs.push_back(v);
                reverse(vs.begin(), vs.end());
                reverse(es.begin(), es.end());
                es.push_back(id);
                return {vs, es};
            }
        }
    }
    return {};
}
