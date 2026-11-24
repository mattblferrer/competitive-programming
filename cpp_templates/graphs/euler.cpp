// Contents
//   euler_directed    Euler path/cycle in a directed graph, as {vertices, edge ids}
//   euler_undirected  Euler path/cycle in an undirected graph, as {vertices, edge ids}

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;

// Euler path/cycle in a directed graph as {vertices, edge ids}: edge ids[i] goes from vertices[i] to vertices[i + 1]
// so there are E + 1 vertices and E edge ids; both are empty if no Euler path exists, O(V + E)
pair<vector<int>, vector<int>> euler_directed(int n, const vector<pair<int, int>> &edges) {
    int m = edges.size();
    vector<vector<pair<int, int>>> adj(n);  // {to, edge id}
    vector<int> in(n), out(n);
    for (int i = 0; i < m; i++) {
        auto [u, v] = edges[i];
        adj[u].push_back({v, i});
        out[u]++;
        in[v]++;
    }
    int start = -1, end = -1, any = -1;
    for (int u = 0; u < n; u++) {
        if (out[u] > 0 && any == -1) any = u;
        if (out[u] == in[u] + 1) {
            if (start != -1) return {};
            start = u;
        } else if (in[u] == out[u] + 1) {
            if (end != -1) return {};
            end = u;
        } else if (in[u] != out[u]) {
            return {};
        }
    }
    if (n == 0 || (start == -1) != (end == -1)) return {};
    if (start == -1) start = any == -1 ? 0 : any;
    vector<pair<int, int>> st{{start, -1}};  // {vertex, edge used to reach it}
    vector<int> verts, ids;
    while (!st.empty()) {
        int u = st.back().first;
        if (adj[u].empty()) {
            verts.push_back(u);
            if (st.back().second != -1) ids.push_back(st.back().second);
            st.pop_back();
        } else {
            st.push_back(adj[u].back());
            adj[u].pop_back();
        }
    }
    if ((int)ids.size() != m) return {};
    reverse(verts.begin(), verts.end());
    reverse(ids.begin(), ids.end());
    return {verts, ids};
}

// Euler path/cycle in an undirected graph as {vertices, edge ids}: edge ids[i] joins vertices[i] and vertices[i + 1]
// so there are E + 1 vertices and E edge ids; both are empty if no Euler path exists, O(V + E)
pair<vector<int>, vector<int>> euler_undirected(int n, const vector<pair<int, int>> &edges) {
    int m = edges.size();
    vector<vector<pair<int, int>>> adj(n);  // {to, edge id}
    vector<int> deg(n);
    for (int i = 0; i < m; i++) {
        auto [u, v] = edges[i];
        adj[u].push_back({v, i});
        adj[v].push_back({u, i});
        deg[u]++;
        deg[v]++;
    }
    int start = -1, odd = 0;
    for (int u = 0; u < n; u++) {
        if (deg[u] > 0 && start == -1) start = u;
        if (deg[u] % 2) odd++;
    }
    for (int u = 0; u < n; u++) if (deg[u] % 2) start = u;  // a path must start at an odd-degree vertex
    if (n == 0 || (odd != 0 && odd != 2)) return {};
    if (start == -1) start = 0;
    vector<char> used(m, false);
    vector<pair<int, int>> st{{start, -1}};  // {vertex, edge used to reach it}
    vector<int> verts, ids;
    while (!st.empty()) {
        int u = st.back().first;
        while (!adj[u].empty() && used[adj[u].back().second]) adj[u].pop_back();
        if (adj[u].empty()) {
            verts.push_back(u);
            if (st.back().second != -1) ids.push_back(st.back().second);
            st.pop_back();
        } else {
            auto [v, id] = adj[u].back();
            used[id] = true;
            st.push_back({v, id});
        }
    }
    if ((int)ids.size() != m) return {};
    return {verts, ids};
}
