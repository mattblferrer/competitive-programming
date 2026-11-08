#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
const ll INF = 2e18;

// maximum bipartite matching (Hopcroft-Karp); left vertices 0..n-1, right vertices 0..m-1
// after max_matching: l[u] = right match of u, r[v] = left match of v, -1 if unmatched
//   HopcroftKarp(n, m)    empty graph, O(n + m)
//   add_edge(u, v)        add the edge from left u to right v, O(1)
//   bfs()                 build the layers; true if an augmenting path exists, O(V + E)
//   dfs(u)                try to augment from left u along the layers, O(V + E) per phase
//   max_matching()        size of the maximum matching, O(E sqrt V)
//   min_vertex_cover()    minimum vertex cover as {left vertices, right vertices} (Konig); call max_matching first, O(V + E)
struct HopcroftKarp {
    int n, m;
    vector<vector<int>> adj;
    vector<int> l, r, dist;

    HopcroftKarp(int n = 0, int m = 0): n(n), m(m), adj(n), l(n, -1), r(m, -1), dist(n) {}

    void add_edge(int u, int v) { adj[u].push_back(v); }

    bool bfs() {
        queue<int> q;
        for (int u = 0; u < n; u++) {
            dist[u] = l[u] == -1 ? 0 : -1;
            if (l[u] == -1) q.push(u);
        }
        bool found = false;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int v : adj[u]) {
                if (r[v] == -1) found = true;
                else if (dist[r[v]] == -1) {
                    dist[r[v]] = dist[u] + 1;
                    q.push(r[v]);
                }
            }
        }
        return found;
    }

    bool dfs(int u) {
        for (int v : adj[u]) {
            if (r[v] == -1 || (dist[r[v]] == dist[u] + 1 && dfs(r[v]))) {
                l[u] = v;
                r[v] = u;
                return true;
            }
        }
        dist[u] = -1;
        return false;
    }

    int max_matching() {
        int res = 0;
        while (bfs()) {
            for (int u = 0; u < n; u++) if (l[u] == -1 && dfs(u)) res++;
        }
        return res;
    }

    pair<vector<int>, vector<int>> min_vertex_cover() {
        vector<char> vis_l(n, false), vis_r(m, false);
        function<void(int)> go = [&](int u) {
            vis_l[u] = true;
            for (int v : adj[u]) {
                if (vis_r[v]) continue;
                vis_r[v] = true;
                if (r[v] != -1 && !vis_l[r[v]]) go(r[v]);
            }
        };
        for (int u = 0; u < n; u++) if (l[u] == -1 && !vis_l[u]) go(u);
        vector<int> left, right;
        for (int u = 0; u < n; u++) if (!vis_l[u]) left.push_back(u);
        for (int v = 0; v < m; v++) if (vis_r[v]) right.push_back(v);
        return {left, right};
    }
};

// minimum cost assignment (Hungarian) of every row to a distinct column; cost is n x m with n <= m, O(n^2 m)
// returns {total cost, match} where match[i] is the column assigned to row i
pair<ll, vector<int>> hungarian(const vector<vector<ll>> &cost) {
    int n = cost.size(), m = n ? cost[0].size() : 0;
    vector<ll> a(n + 1), b(m + 1);
    vector<int> p(m + 1), way(m + 1);  // p[j] = row matched to column j (1-indexed, 0 = none)
    for (int i = 1; i <= n; i++) {
        p[0] = i;
        int j0 = 0;
        vector<ll> minv(m + 1, INF);
        vector<char> used(m + 1, false);
        do {
            used[j0] = true;
            int i0 = p[j0], j1 = 0;
            ll delta = INF;
            for (int j = 1; j <= m; j++) {
                if (used[j]) continue;
                ll cur = cost[i0 - 1][j - 1] - a[i0] - b[j];
                if (cur < minv[j]) {
                    minv[j] = cur;
                    way[j] = j0;
                }
                if (minv[j] < delta) {
                    delta = minv[j];
                    j1 = j;
                }
            }
            for (int j = 0; j <= m; j++) {
                if (used[j]) {
                    a[p[j]] += delta;
                    b[j] -= delta;
                } else {
                    minv[j] -= delta;
                }
            }
            j0 = j1;
        } while (p[j0] != 0);
        for (; j0 != 0; j0 = way[j0]) p[j0] = p[way[j0]];
    }
    vector<int> match(n, -1);
    for (int j = 1; j <= m; j++) if (p[j]) match[p[j] - 1] = j - 1;
    return {-b[0], match};
}

// maximum matching in a general graph (Edmonds' blossom)
// after run: match[v] = partner of v, -1 if unmatched
//   Blossom(n)          empty graph on n vertices, O(n)
//   add_edge(u, v)      add the undirected edge u - v (self-loops are ignored), O(1)
//   lca(a, b)           base of the blossom formed by the alternating paths from a and b, O(V)
//   mark_path(v, b, c)  mark the blossom vertices on the path from v up to base b, O(V)
//   find_path(root)     BFS for an augmenting path from root, returns its end or -1, O(V^2)
//   run()               size of the maximum matching, O(V^3)
struct Blossom {
    int n;
    vector<vector<int>> adj;
    vector<int> match, par, base;
    vector<char> used, in_blossom;

    Blossom(int n = 0): n(n), adj(n), match(n, -1), par(n), base(n), used(n), in_blossom(n) {}

    void add_edge(int u, int v) {
        if (u == v) return;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    int lca(int a, int b) {
        vector<char> seen(n, false);
        while (true) {
            a = base[a];
            seen[a] = true;
            if (match[a] == -1) break;
            a = par[match[a]];
        }
        while (true) {
            b = base[b];
            if (seen[b]) return b;
            b = par[match[b]];
        }
    }

    void mark_path(int v, int b, int child) {
        while (base[v] != b) {
            in_blossom[base[v]] = in_blossom[base[match[v]]] = true;
            par[v] = child;
            child = match[v];
            v = par[match[v]];
        }
    }

    int find_path(int root) {
        fill(used.begin(), used.end(), false);
        fill(par.begin(), par.end(), -1);
        iota(base.begin(), base.end(), 0);
        queue<int> q;
        q.push(root);
        used[root] = true;
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (int to : adj[v]) {
                if (base[v] == base[to] || match[v] == to) continue;
                if (to == root || (match[to] != -1 && par[match[to]] != -1)) {
                    int cur = lca(v, to);
                    fill(in_blossom.begin(), in_blossom.end(), false);
                    mark_path(v, cur, to);
                    mark_path(to, cur, v);
                    for (int i = 0; i < n; i++) {
                        if (in_blossom[base[i]]) {
                            base[i] = cur;
                            if (!used[i]) {
                                used[i] = true;
                                q.push(i);
                            }
                        }
                    }
                } else if (par[to] == -1) {
                    par[to] = v;
                    if (match[to] == -1) return to;
                    used[match[to]] = true;
                    q.push(match[to]);
                }
            }
        }
        return -1;
    }

    int run() {
        int res = 0;
        for (int v = 0; v < n; v++) {
            if (match[v] != -1) continue;
            int u = find_path(v);
            if (u != -1) res++;
            while (u != -1) {
                int pv = par[u], next = match[pv];
                match[u] = pv;
                match[pv] = u;
                u = next;
            }
        }
        return res;
    }
};

// stable marriage (Gale-Shapley), O(n^2): men[i] and women[i] are preference lists, best first
// returns res where res[m] is the woman matched to man m; the result is man-optimal
vector<int> stable_marriage(const vector<vector<int>> &men, const vector<vector<int>> &women) {
    int n = men.size();
    vector<int> at(n, 0), engaged(n, -1), res(n, -1);
    vector<vector<int>> rank(n, vector<int>(n));
    queue<int> q;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) rank[i][women[i][j]] = j;
        q.push(i);
    }
    while (!q.empty()) {
        int m = q.front();
        q.pop();
        while (true) {
            int w = men[m][at[m]++];
            if (engaged[w] != -1) {
                if (rank[w][m] > rank[w][engaged[w]]) continue;
                q.push(engaged[w]);
            }
            engaged[w] = m;
            res[m] = w;
            break;
        }
    }
    return res;
}
