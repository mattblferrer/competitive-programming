// Contents
//   directed_cycle    edge ids of some directed cycle in order, empty if the graph is acyclic
//   undirected_cycle  some cycle of an undirected multigraph as {vertices, edge ids}, both empty if it is a forest
//   FunctionalGraph   cycles, tails and depths of v -> f[v]; f^k(v) and the distance from u to v, O(log n)

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

// functional graph v -> f[v]: each component is one cycle with in-trees hanging off it
//   cycles[c]     vertices of cycle c in order, cycles[c][i + 1] = f[cycles[c][i]]
//   cyc[v]        id of the cycle that v reaches; pos[v] = index of v in it, -1 if v is not on a cycle
//   root[v]       first cycle vertex reached from v; depth[v] = steps to get there (0 on a cycle)
//   FunctionalGraph(f)   O(n log n)
//   jump(v, k)           f^k(v) for any k >= 0, O(log n)
//   dist(u, v)           smallest k >= 0 with f^k(u) = v, -1 if there is none, O(log n)
struct FunctionalGraph {
    int n, LOG = 1;
    vector<int> cyc, pos, root, depth;
    vector<vector<int>> cycles, up;  // up[j][v] = f^(2^j)(v)

    FunctionalGraph(const vector<int> &f): n(f.size()), cyc(n), pos(n, -1), root(n), depth(n) {
        vector<char> state(n);  // 0 unseen, 1 on the current walk, 2 done
        for (int s = 0; s < n; s++) {
            vector<int> walk;
            int v = s;
            while (!state[v]) state[v] = 1, walk.push_back(v), v = f[v];
            if (state[v] == 1) {  // the walk ran into itself: v starts a new cycle
                cycles.emplace_back();
                int u = v;
                do {
                    cyc[u] = cycles.size() - 1, pos[u] = cycles.back().size(), root[u] = u;
                    cycles.back().push_back(u);
                    u = f[u];
                } while (u != v);
            }
            for (int i = walk.size() - 1; i >= 0; i--) {
                int u = walk[i];
                state[u] = 2;
                if (pos[u] < 0) cyc[u] = cyc[f[u]], root[u] = root[f[u]], depth[u] = depth[f[u]] + 1;
            }
        }
        while ((1 << LOG) < n) LOG++;
        up.assign(LOG, f);
        for (int j = 1; j < LOG; j++) for (int v = 0; v < n; v++) up[j][v] = up[j - 1][up[j - 1][v]];
    }

    int jump(int v, ll k) const {
        if (k >= depth[v]) {
            auto &c = cycles[cyc[v]];
            return c[(pos[root[v]] + (k - depth[v])) % c.size()];
        }
        for (int j = 0; k; j++, k >>= 1) if (k & 1) v = up[j][v];
        return v;
    }

    ll dist(int u, int v) const {
        if (pos[v] >= 0) {
            if (cyc[u] != cyc[v]) return -1;
            int L = cycles[cyc[v]].size();
            return depth[u] + (pos[v] - pos[root[u]] + L) % L;
        }
        if (root[u] != root[v] || depth[u] < depth[v]) return -1;
        return jump(u, depth[u] - depth[v]) == v ? depth[u] - depth[v] : -1;
    }
};
