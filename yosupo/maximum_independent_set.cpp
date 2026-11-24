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

void solve() {
    ll n, m;
    cin >> n >> m;
    vector<vector<bool>> adj(n, vector<bool>(n, false));
    for (ll i = 0; i < m; i++) {
        ll u, v;
        cin >> u >> v;
        adj[u][v] = adj[v][u] = true;
    }
    MaxClique<40> mc(n);
    for (ll u = 0; u < n; u++) {
        for (ll v = u + 1; v < n; v++) if (!adj[u][v]) mc.add_edge(u, v);
    }
    vector<int> best = mc.max_clique();
    cout << best.size() << "\n";
    for (ll i = 0; i < best.size(); i++) cout << best[i] << " ";
    cout << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(20);

    int t = 1;
    // cin >> t;  // comment out for single test
    while (t--) solve();
}
