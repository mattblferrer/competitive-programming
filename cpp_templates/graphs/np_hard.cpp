// Contents
//   MaxClique         cliques in a graph on at most N vertices, exponential in the worst case
//   chromatic_number  fewest colors for a proper vertex coloring (inclusion-exclusion over independent sets)
//   steiner_tree      cheapest connected subgraph containing all terminals (Steiner tree), as {weight, edge ids}

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
const ll INF = 2e18;

// cliques in a graph on at most N vertices, exponential in the worst case; a maximum independent set is a maximum clique of the complement
//   MaxClique(n)       empty graph on n vertices, O(n)
//   add_edge(u, v)     add the undirected edge u - v (self-loops are ignored), O(1)
//   enumerate(f)       call f(r) with a bitset r for every maximal clique (Bron-Kerbosch with pivoting), O(3^(n/3)) calls at most
//   max_clique()       vertices of a maximum clique (branch and bound with a greedy coloring bound)
template <int N = 128>
struct MaxClique {
    using B = bitset<N>;
    int n;
    vector<B> adj;
    vector<int> cur, best;

    MaxClique(int n = 0): n(n), adj(n) {}

    void add_edge(int u, int v) {
        if (u == v) return;
        adj[u].set(v);
        adj[v].set(u);
    }

    template <class F>
    void go(B r, B p, B x, F &f) {
        if (p.none()) {
            if (x.none()) f(r);
            return;
        }
        B both = p | x;
        int pivot = -1, most = -1;
        for (int v = both._Find_first(); v < N; v = both._Find_next(v)) {
            int c = (p & adj[v]).count();
            if (c > most) most = c, pivot = v;
        }
        B cand = p & ~adj[pivot];
        for (int v = cand._Find_first(); v < N; v = cand._Find_next(v)) {
            B with = r;
            with.set(v);
            go(with, p & adj[v], x & adj[v], f);
            p.reset(v);
            x.set(v);
        }
    }

    template <class F>
    void enumerate(F f) {
        B p;
        for (int i = 0; i < n; i++) p.set(i);
        go(B(), p, B(), f);
    }

    void expand(B p) {
        vector<int> order, color;
        B left = p;
        for (int c = 1; left.any(); c++) {  // vertices of one color are pairwise non-adjacent, so a clique uses at most one of them
            B q = left;
            while (q.any()) {
                int v = q._Find_first();
                order.push_back(v);
                color.push_back(c);
                left.reset(v);
                q.reset(v);
                q &= ~adj[v];
            }
        }
        for (int i = (int)order.size() - 1; i >= 0; i--) {
            if (cur.size() + color[i] <= best.size()) return;
            int v = order[i];
            cur.push_back(v);
            B np = p & adj[v];
            if (np.any()) expand(np);
            else if (cur.size() > best.size()) best = cur;
            cur.pop_back();
            p.reset(v);
        }
    }

    vector<int> max_clique() {
        B p;
        for (int i = 0; i < n; i++) p.set(i);
        cur.clear();
        best.clear();
        expand(p);
        sort(best.begin(), best.end());
        return best;
    }
};

// fewest colors for a proper vertex coloring (inclusion-exclusion over independent sets), O(2^n n) time, O(2^n) memory, n up to about 23
// checks two primes, so a wrong answer needs both to cancel by chance; edges are {u, v}, self-loops are ignored
int chromatic_number(int n, const vector<pair<int, int>> &edges) {
    if (n == 0) return 0;
    const ll M1 = 998'244'353, M2 = 1'000'000'007;
    vector<int> adj(n);
    for (auto [u, v] : edges) {
        if (u == v) continue;
        adj[u] |= 1 << v;
        adj[v] |= 1 << u;
    }
    int full = 1 << n;
    vector<int> ind(full, 1), g1(full, 1), g2(full, 1);  // ind[S] = number of independent subsets of S
    for (int s = 1; s < full; s++) {
        int v = __builtin_ctz(s), rest = s ^ (1 << v);
        ind[s] = ind[rest] + ind[rest & ~adj[v]];
    }
    for (int k = 1; k < n; k++) {  // g[S] = ways to choose k independent sets inside S, in order
        ll s1 = 0, s2 = 0;
        for (int s = 0; s < full; s++) {
            g1[s] = g1[s] * (ll)ind[s] % M1;
            g2[s] = g2[s] * (ll)ind[s] % M2;
            bool neg = (n - __builtin_popcount(s)) & 1;
            s1 += neg ? M1 - g1[s] : g1[s];
            s2 += neg ? M2 - g2[s] : g2[s];
        }
        if (s1 % M1 != 0 || s2 % M2 != 0) return k;
    }
    return n;
}

// cheapest connected subgraph containing all terminals (Steiner tree): returns {total weight, edge ids}, {INF, {}} if impossible
// edges are {u, v, w} with w >= 0; k = number of terminals, O(3^k V + 2^k E log V)
pair<ll, vector<int>> steiner_tree(int n, const vector<array<ll, 3>> &edges, const vector<int> &terminals) {
    int k = terminals.size();
    if (k == 0) return {0, {}};
    vector<vector<pair<int, int>>> adj(n);  // {to, edge id}
    for (int i = 0; i < (int)edges.size(); i++) {
        adj[edges[i][0]].push_back({(int)edges[i][1], i});
        adj[edges[i][1]].push_back({(int)edges[i][0], i});
    }
    // dp[mask][v] = cheapest tree containing mask and v; it came from edge via[mask][v] if >= 0,
    // else from the split sub[mask][v] if > 0, else it is a terminal on its own
    vector<vector<ll>> dp(1 << k, vector<ll>(n, INF));
    vector<vector<int>> via(1 << k, vector<int>(n, -1)), sub(1 << k, vector<int>(n, 0));
    for (int i = 0; i < k; i++) dp[1 << i][terminals[i]] = 0;
    for (int mask = 1; mask < (1 << k); mask++) {
        vector<ll> &d = dp[mask];
        for (int s = (mask - 1) & mask; s; s = (s - 1) & mask) {
            if (s < (mask ^ s)) continue;  // each split only needs trying once
            for (int v = 0; v < n; v++) {
                if (dp[s][v] < INF && dp[mask ^ s][v] < INF && dp[s][v] + dp[mask ^ s][v] < d[v]) {
                    d[v] = dp[s][v] + dp[mask ^ s][v];
                    sub[mask][v] = s;
                }
            }
        }
        priority_queue<pll, vector<pll>, greater<pll>> pq;
        for (int v = 0; v < n; v++) if (d[v] < INF) pq.push({d[v], v});
        while (!pq.empty()) {
            auto [cost, u] = pq.top();
            pq.pop();
            if (cost != d[u]) continue;
            for (auto [v, id] : adj[u]) {
                if (cost + edges[id][2] < d[v]) {
                    d[v] = cost + edges[id][2];
                    via[mask][v] = id;
                    pq.push({d[v], v});
                }
            }
        }
    }
    int full = (1 << k) - 1;
    if (dp[full][terminals[0]] == INF) return {INF, {}};
    vector<int> used;
    vector<pair<int, int>> st{{full, terminals[0]}};
    while (!st.empty()) {
        auto [mask, v] = st.back();
        st.pop_back();
        if (int id = via[mask][v]; id >= 0) {
            used.push_back(id);
            st.push_back({mask, int(edges[id][0] ^ edges[id][1] ^ v)});
        } else if (int s = sub[mask][v]) {
            st.push_back({s, v});
            st.push_back({mask ^ s, v});
        }
    }
    sort(used.begin(), used.end());
    used.erase(unique(used.begin(), used.end()), used.end());  // only zero-weight edges can repeat
    return {dp[full][terminals[0]], used};
}
