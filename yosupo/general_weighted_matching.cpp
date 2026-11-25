// github.com/mattblferrer/competitive-programming

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
using ull = unsigned long long;
const ld PI = acosl(-1);
const ll INF = 2e18;
const ll MOD = 1'000'000'007;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

#ifdef LOCAL
#define dbg(x) cerr << #x << " = " << (x) << '\n'
#else
#define dbg(x)
#endif

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

void solve() {
    ll n, m;
    cin >> n >> m;
    WeightedBlossom b(n);
    for (ll i = 0; i < m; i++) {
        ll u, v, w;
        cin >> u >> v >> w;
        b.add_edge(u, v, w);
    }
    auto [total, cnt] = b.run();
    cout << cnt << " " << total << "\n";
    for (ll i = 0; i < n; i++) {
        if (i < b.match[i]) cout << i << " " << b.match[i] << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(20);

    int t = 1;
    // cin >> t;  // comment out for single test
    while (t--) solve();
}
