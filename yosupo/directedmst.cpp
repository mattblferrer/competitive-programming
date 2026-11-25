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

// minimum spanning arborescence (Chu-Liu/Edmonds, Tarjan's version with mergeable heaps): every vertex is reachable
// from root by chosen edges; call find_min only once per object, since it uses up the heaps
//   Arborescence(n)     empty graph on n vertices, O(n)
//   add_edge(u, v, w)   add the directed edge u -> v, returns its id, O(log E)
//   find_min(root)      for each vertex, the id of the edge entering it (-1 for root); empty if impossible, O(E log E)
// find_min follows cheapest entering edges from each vertex until it reaches the root's tree or closes a cycle; a cycle
// is contracted (DSU) with its heaps merged and charged its chosen weights, and contractions are undone at the end
struct Arborescence {
    struct Edge { int from, to; ll w; };
    int n;
    vector<Edge> e;
    vector<int> heap, lc, rc, rk;  // leftist heap of edge ids entering each vertex; rk = length of the right spine
    vector<ll> key, lazy;          // key = weight minus what was charged so far, lazy = pending add for the subtree

    Arborescence(int n = 0): n(n), heap(n, -1) {}

    void push(int x) {
        for (int c : {lc[x], rc[x]}) if (c >= 0) lazy[c] += lazy[x];
        key[x] += lazy[x];
        lazy[x] = 0;
    }

    int merge(int a, int b) {  // recurses down right spines only, so O(log E) deep
        if (a < 0 || b < 0) return a < 0 ? b : a;
        push(a), push(b);
        if (key[b] < key[a]) swap(a, b);
        rc[a] = merge(rc[a], b);
        if (lc[a] < 0 || rk[lc[a]] < rk[rc[a]]) swap(lc[a], rc[a]);
        rk[a] = rc[a] < 0 ? 1 : rk[rc[a]] + 1;
        return a;
    }

    int add_edge(int u, int v, ll w) {
        int id = e.size();
        e.push_back({u, v, w});
        lc.push_back(-1), rc.push_back(-1), rk.push_back(1), key.push_back(w), lazy.push_back(0);
        heap[v] = merge(heap[v], id);
        return id;
    }

    vector<int> find_min(int r) {
        vector<int> p(n, -1), seen(n, -1), path(n), q(n), in(n, -1);  // p = DSU without path compression, for undo
        vector<pair<int, int>> hist;                                   // {merged root, its old p}
        vector<tuple<int, int, vector<int>>> cycles;                   // {contracted vertex, hist size, cycle edges}
        auto find = [&](int x) {
            while (p[x] >= 0) x = p[x];
            return x;
        };
        auto join = [&](int a, int b) {
            a = find(a), b = find(b);
            if (a == b) return false;
            if (p[a] > p[b]) swap(a, b);
            hist.push_back({b, p[b]});
            p[a] += p[b], p[b] = a;
            return true;
        };
        seen[r] = r;
        for (int s = 0; s < n; s++) {
            int u = s, len = 0;
            while (seen[u] < 0) {
                if (heap[u] < 0) return {};
                int x = heap[u];
                push(x);
                heap[u] = merge(lc[x], rc[x]);
                if (heap[u] >= 0) lazy[heap[u]] -= key[x];  // charge the chosen weight to the other entering edges
                q[len] = x, path[len++] = u, seen[u] = s;
                u = find(e[x].from);
                if (seen[u] == s) {  // closed a cycle: contract it into one vertex
                    int h = -1, end = len, t = hist.size(), w;
                    do h = merge(h, heap[w = path[--len]]);
                    while (join(u, w));
                    u = find(u), heap[u] = h, seen[u] = -1;
                    cycles.push_back({u, t, vector<int>(q.begin() + len, q.begin() + end)});
                }
            }
            for (int i = 0; i < len; i++) in[find(e[q[i]].to)] = q[i];
        }
        for (int k = (int)cycles.size() - 1; k >= 0; k--) {  // expand, last contracted first
            auto &[u, t, cyc] = cycles[k];
            for (; (int)hist.size() > t; hist.pop_back()) {
                auto [b, old] = hist.back();
                p[p[b]] -= old, p[b] = old;
            }
            int keep = in[u];  // the edge entering the cycle stays, the cycle edge into the same vertex goes
            for (int x : cyc) in[find(e[x].to)] = x;
            in[find(e[keep].to)] = keep;
        }
        return in;
    }
};

void solve() {
    ll n, m, s;
    cin >> n >> m >> s;
    Arborescence g(n);
    for (ll i = 0; i < m; i++) {
        ll a, b, c;
        cin >> a >> b >> c;
        g.add_edge(a, b, c);
    }
    vector<int> in = g.find_min(s);
    ll total = 0;
    for (ll i = 0; i < n; i++) if (i != s) total += g.e[in[i]].w;
    cout << total << "\n";
    for (ll i = 0; i < n; i++) cout << (i == s ? s : g.e[in[i]].from) << " ";
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
