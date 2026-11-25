// Contents
//   SCC                    strongly connected components (Tarjan, iterative so deep graphs can't overflow the stack), 0-indexed
//   TwoSat                 2-SAT, uses SCC above
//   complement_components  connected components of the complement of a simple graph, O(n + m)

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;

// strongly connected components (Tarjan, iterative so deep graphs can't overflow the stack), 0-indexed
// component ids are in reverse topological order: an edge u -> v between components has comp[u] > comp[v]
//   SCC(n)         empty graph on n vertices, O(n)
//   add_edge(u, v) add the directed edge u -> v, O(1)
//   dfs(s)         visit everything reachable from s and pop finished components, O(V + E) total
//   run()          compute comp[] and returns the number of components, O(V + E)
struct SCC {
    int n, timer = 0, count = 0;
    vector<vector<int>> adj;
    vector<int> id, low, comp, st;

    SCC(int n = 0): n(n), adj(n), id(n, -1), low(n), comp(n, -1) {}

    void add_edge(int u, int v) { adj[u].push_back(v); }

    void dfs(int s) {
        vector<pair<int, int>> call;  // {vertex, index of its next edge}, the recursion stack
        auto enter = [&](int u) {
            id[u] = low[u] = timer++;
            st.push_back(u);
            call.push_back({u, 0});
        };
        enter(s);
        while (!call.empty()) {
            int u = call.back().first, i = call.back().second;
            if (i < (int)adj[u].size()) {
                call.back().second++;
                int v = adj[u][i];
                if (id[v] == -1) enter(v);
                else if (comp[v] == -1) low[u] = min(low[u], id[v]);
                continue;
            }
            call.pop_back();  // u is finished: return to its parent
            if (!call.empty()) low[call.back().first] = min(low[call.back().first], low[u]);
            if (id[u] == low[u]) {
                int v;
                do {
                    v = st.back();
                    st.pop_back();
                    comp[v] = count;
                } while (v != u);
                count++;
            }
        }
    }

    int run() {
        for (int u = 0; u < n; u++) if (id[u] == -1) dfs(u);
        return count;
    }
};

// 2-SAT, uses SCC above
//   TwoSat(n)              n boolean variables, O(n)
//   add_or(a, fa, b, fb)   require (a == fa) or (b == fb), O(1)
//   solve()                true if satisfiable, and fills val[i] with a valid assignment, O(n + clauses)
struct TwoSat {
    int n;
    SCC scc;
    vector<char> val;

    TwoSat(int n = 0): n(n), scc(2 * n), val(n) {}

    void add_or(int a, bool fa, int b, bool fb) {
        scc.add_edge(2 * a + !fa, 2 * b + fb);
        scc.add_edge(2 * b + !fb, 2 * a + fa);
    }

    bool solve() {
        scc.run();
        for (int i = 0; i < n; i++) {
            if (scc.comp[2 * i] == scc.comp[2 * i + 1]) return false;
            val[i] = scc.comp[2 * i + 1] < scc.comp[2 * i];  // node 2i + 1 is "i is true"
        }
        return true;
    }
};

// connected components of the complement of a simple undirected graph, 0-indexed; BFS that only scans vertices not
// yet visited, keeping the ones adjacent to the current vertex for later (each kept vertex is paid for by an edge), O(n + m)
vector<vector<int>> complement_components(const vector<vector<int>> &adj) {
    int n = adj.size();
    vector<int> left(n), mark(n, -1);
    iota(left.begin(), left.end(), 0);
    vector<vector<int>> comps;
    while (!left.empty()) {
        vector<int> comp{left.back()};
        left.pop_back();
        for (size_t i = 0; i < comp.size(); i++) {
            int u = comp[i];
            for (int v : adj[u]) mark[v] = u;
            vector<int> keep;
            for (int v : left) (mark[v] == u ? keep : comp).push_back(v);
            left.swap(keep);
        }
        comps.push_back(comp);
    }
    return comps;
}
