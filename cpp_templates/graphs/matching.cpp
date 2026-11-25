// Contents
//   HopcroftKarp     maximum bipartite matching (Hopcroft-Karp); left vertices 0..n-1, right vertices 0..m-1
//   hungarian        minimum cost assignment (Hungarian) of every row to a distinct column
//   Blossom          maximum matching in a general graph (Edmonds' blossom)
//   WeightedBlossom  maximum weight matching in a general graph (Edmonds' blossom with dual variables), O(n^3)
//   stable_marriage  stable marriage (Gale-Shapley), O(n^2): men[i] and women[i] are preference lists

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

    bool dfs(int s) {  // iterative: call holds {left vertex, index of the edge being tried}
        vector<pair<int, int>> call{{s, 0}};
        while (!call.empty()) {
            auto [u, i] = call.back();
            if (i == (int)adj[u].size()) {  // dead end: never try u again this phase
                dist[u] = -1;
                call.pop_back();
                if (!call.empty()) call.back().second++;
                continue;
            }
            int v = adj[u][i];
            if (r[v] == -1) {  // free right vertex: flip the matching along the whole path
                for (auto [x, j] : call) {
                    l[x] = adj[x][j];
                    r[adj[x][j]] = x;
                }
                return true;
            }
            if (dist[r[v]] == dist[u] + 1) call.push_back({r[v], 0});
            else call.back().second++;
        }
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
        vector<int> st;  // alternating paths from the free left vertices
        for (int s = 0; s < n; s++) {
            if (l[s] != -1) continue;
            vis_l[s] = true;
            st.push_back(s);
        }
        while (!st.empty()) {
            int u = st.back();
            st.pop_back();
            for (int v : adj[u]) {
                if (vis_r[v]) continue;
                vis_r[v] = true;
                if (r[v] != -1 && !vis_l[r[v]]) {
                    vis_l[r[v]] = true;
                    st.push_back(r[v]);
                }
            }
        }
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

// maximum weight matching in a general graph (Edmonds' blossom with dual variables), 0-indexed; the matching need
// not be perfect. Internally vertices are 1..n and blossoms n+1..2n; lab are the duals (vertex labels doubled
// against the weights), an edge is tight when lab[u] + lab[v] = 2 w, and each phase grows alternating trees on
// tight edges, shrinking odd cycles into blossoms, until it augments or the free vertices' labels reach 0
// after run: match[v] = partner of v, -1 if unmatched
//   WeightedBlossom(n)   empty graph on n vertices, O(n^2)
//   add_edge(u, v, w)    add the undirected edge u - v of weight w (the heaviest copy is kept; w <= 0 is ignored), O(1)
//   run()                {total weight, number of edges} of a maximum weight matching, O(n^3)
struct WeightedBlossom {
    struct Edge {
        int u, v;
        ll w;
    };
    int n, nx;
    vector<vector<Edge>> g;
    vector<ll> lab;
    vector<int> mate, slack, st, pa, S, vis, match;  // mate is 1-indexed, 0 = unmatched; S: 0 outer, 1 inner, -1 free
    vector<vector<int>> flower_from, flower;
    queue<int> q;
    int stamp = 0;

    WeightedBlossom(int n): n(n), nx(n), g(2 * n + 1, vector<Edge>(2 * n + 1)), lab(2 * n + 1), mate(2 * n + 1),
        slack(2 * n + 1), st(2 * n + 1), pa(2 * n + 1), S(2 * n + 1), vis(2 * n + 1), match(n, -1),
        flower_from(2 * n + 1, vector<int>(n + 1)), flower(2 * n + 1) {
        for (int u = 1; u <= n; u++) for (int v = 1; v <= n; v++) g[u][v] = {u, v, 0};
    }

    void add_edge(int u, int v, ll w) {
        if (u == v || w <= 0) return;
        u++, v++;
        if (w > g[u][v].w) g[u][v].w = g[v][u].w = w;
    }

    ll dist(const Edge &e) { return lab[e.u] + lab[e.v] - 2 * e.w; }

    void update_slack(int u, int x) {
        if (!slack[x] || dist(g[u][x]) < dist(g[slack[x]][x])) slack[x] = u;
    }

    void set_slack(int x) {
        slack[x] = 0;
        for (int u = 1; u <= n; u++) if (g[u][x].w > 0 && st[u] != x && S[st[u]] == 0) update_slack(u, x);
    }

    void q_push(int x) {
        if (x <= n) q.push(x);
        else for (int y : flower[x]) q_push(y);
    }

    void set_st(int x, int b) {
        st[x] = b;
        if (x > n) for (int y : flower[x]) set_st(y, b);
    }

    int get_pr(int b, int xr) {  // position of xr in flower b, reversing the cycle so that it is even
        int pr = find(flower[b].begin(), flower[b].end(), xr) - flower[b].begin();
        if (pr % 2 == 0) return pr;
        reverse(flower[b].begin() + 1, flower[b].end());
        return (int)flower[b].size() - pr;
    }

    void set_match(int u, int v) {
        mate[u] = g[u][v].v;
        if (u <= n) return;
        Edge e = g[u][v];
        int xr = flower_from[u][e.u], pr = get_pr(u, xr);
        for (int i = 0; i < pr; i++) set_match(flower[u][i], flower[u][i ^ 1]);
        set_match(xr, v);
        rotate(flower[u].begin(), flower[u].begin() + pr, flower[u].end());
    }

    void augment(int u, int v) {
        while (true) {
            int xnv = st[mate[u]];
            set_match(u, v);
            if (!xnv) return;
            set_match(xnv, st[pa[xnv]]);
            u = st[pa[xnv]], v = xnv;
        }
    }

    int get_lca(int u, int v) {
        for (stamp++; u || v; swap(u, v)) {
            if (!u) continue;
            if (vis[u] == stamp) return u;
            vis[u] = stamp;
            u = st[mate[u]];
            if (u) u = st[pa[u]];
        }
        return 0;
    }

    void add_blossom(int u, int lca, int v) {
        int b = n + 1;
        while (b <= nx && st[b]) b++;
        if (b > nx) nx++;
        lab[b] = 0, S[b] = 0;
        mate[b] = mate[lca];
        flower[b] = {lca};
        for (int x = u, y; x != lca; x = st[pa[y]]) {
            flower[b].push_back(x), flower[b].push_back(y = st[mate[x]]);
            q_push(y);
        }
        reverse(flower[b].begin() + 1, flower[b].end());
        for (int x = v, y; x != lca; x = st[pa[y]]) {
            flower[b].push_back(x), flower[b].push_back(y = st[mate[x]]);
            q_push(y);
        }
        set_st(b, b);
        for (int x = 1; x <= nx; x++) g[b][x].w = g[x][b].w = 0;
        for (int x = 1; x <= n; x++) flower_from[b][x] = 0;
        for (int xs : flower[b]) {
            for (int x = 1; x <= nx; x++) {
                if (g[xs][x].w > 0 && (g[b][x].w == 0 || dist(g[xs][x]) < dist(g[b][x]))) {
                    g[b][x] = g[xs][x], g[x][b] = g[x][xs];
                }
            }
            for (int x = 1; x <= n; x++) if (flower_from[xs][x]) flower_from[b][x] = xs;
        }
        set_slack(b);
    }

    void expand_blossom(int b) {  // an inner blossom whose label reached 0
        for (int x : flower[b]) set_st(x, x);
        int xr = flower_from[b][g[b][pa[b]].u], pr = get_pr(b, xr);
        for (int i = 0; i < pr; i += 2) {
            int xs = flower[b][i], xns = flower[b][i + 1];
            pa[xs] = g[xns][xs].u;
            S[xs] = 1, S[xns] = 0;
            slack[xs] = 0, set_slack(xns);
            q_push(xns);
        }
        S[xr] = 1, pa[xr] = pa[b];
        for (int i = pr + 1; i < (int)flower[b].size(); i++) {
            int xs = flower[b][i];
            S[xs] = -1, set_slack(xs);
        }
        st[b] = 0;
    }

    bool on_found_edge(const Edge &e) {  // a tight edge out of an outer vertex; true if it augmented
        int u = st[e.u], v = st[e.v];
        if (S[v] == -1) {
            pa[v] = e.u, S[v] = 1;
            int nu = st[mate[v]];
            slack[v] = slack[nu] = 0;
            S[nu] = 0, q_push(nu);
        } else if (S[v] == 0) {
            int lca = get_lca(u, v);
            if (!lca) return augment(u, v), augment(v, u), true;
            add_blossom(u, lca, v);
        }
        return false;
    }

    bool phase() {  // one augmentation; false when no augmenting path can raise the weight
        fill(S.begin() + 1, S.begin() + nx + 1, -1);
        fill(slack.begin() + 1, slack.begin() + nx + 1, 0);
        q = queue<int>();
        for (int x = 1; x <= nx; x++) if (st[x] == x && !mate[x]) pa[x] = 0, S[x] = 0, q_push(x);
        if (q.empty()) return false;
        while (true) {
            while (!q.empty()) {
                int u = q.front();
                q.pop();
                if (S[st[u]] == 1) continue;
                for (int v = 1; v <= n; v++) {
                    if (g[u][v].w == 0 || st[u] == st[v]) continue;
                    if (dist(g[u][v]) == 0) {
                        if (on_found_edge(g[u][v])) return true;
                    } else update_slack(u, st[v]);
                }
            }
            ll d = LLONG_MAX;
            for (int b = n + 1; b <= nx; b++) if (st[b] == b && S[b] == 1) d = min(d, lab[b] / 2);
            for (int x = 1; x <= nx; x++) {
                if (st[x] != x || !slack[x]) continue;
                if (S[x] == -1) d = min(d, dist(g[slack[x]][x]));
                else if (S[x] == 0) d = min(d, dist(g[slack[x]][x]) / 2);
            }
            for (int u = 1; u <= n; u++) {
                if (S[st[u]] == 0) {
                    if (lab[u] <= d) return false;
                    lab[u] -= d;
                } else if (S[st[u]] == 1) lab[u] += d;
            }
            for (int b = n + 1; b <= nx; b++) {
                if (st[b] != b) continue;
                if (S[b] == 0) lab[b] += d * 2;
                else if (S[b] == 1) lab[b] -= d * 2;
            }
            q = queue<int>();
            for (int x = 1; x <= nx; x++) {
                if (st[x] == x && slack[x] && st[slack[x]] != x && dist(g[slack[x]][x]) == 0) {
                    if (on_found_edge(g[slack[x]][x])) return true;
                }
            }
            for (int b = n + 1; b <= nx; b++) if (st[b] == b && S[b] == 1 && lab[b] == 0) expand_blossom(b);
        }
    }

    pair<ll, int> run() {
        ll w_max = 0;
        for (int u = 1; u <= n; u++) {
            st[u] = u;
            for (int v = 1; v <= n; v++) flower_from[u][v] = u == v ? u : 0, w_max = max(w_max, g[u][v].w);
        }
        for (int u = 1; u <= n; u++) lab[u] = w_max;
        int cnt = 0;
        while (phase()) cnt++;
        ll total = 0;
        for (int u = 1; u <= n; u++) {
            match[u - 1] = mate[u] - 1;
            if (mate[u] && mate[u] < u) total += g[u][mate[u]].w;
        }
        return {total, cnt};
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
