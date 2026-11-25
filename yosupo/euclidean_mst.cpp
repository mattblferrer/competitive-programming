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

// minimum spanning forest (Kruskal), edges are {w, u, v}; returns {total weight, indices of the chosen edges}, O(E log E)
pair<ll, vector<int>> kruskal(int n, const vector<array<ll, 3>> &edges) {
    vector<int> p(n), order(edges.size()), chosen;
    iota(p.begin(), p.end(), 0);
    iota(order.begin(), order.end(), 0);
    sort(order.begin(), order.end(), [&](int a, int b) { return edges[a] < edges[b]; });
    auto find_set = [&](int x) {  // path halving, no recursion
        while (p[x] != x) x = p[x] = p[p[x]];
        return x;
    };
    ll total = 0;
    for (int i : order) {
        int u = find_set(edges[i][1]), v = find_set(edges[i][2]);
        if (u == v) continue;
        p[u] = v;
        total += edges[i][0];
        chosen.push_back(i);
    }
    return {total, chosen};
}

// Delaunay triangulation of integer points (Guibas-Stolfi divide and conquer on quad-edges): its edges as index pairs;
// a repeated point is joined to its first copy and collinear points to their neighbours on the line. A Euclidean MST
// only uses these edges (pass them to kruskal with squared lengths); exact for |coordinates| up to ~5e8, O(n log n)
vector<pair<int, int>> delaunay_edges(const vector<pll> &pts) {
    int n = pts.size();
    vector<int> ord(n), id;
    iota(ord.begin(), ord.end(), 0);
    sort(ord.begin(), ord.end(), [&](int a, int b) { return pts[a] < pts[b]; });
    vector<pll> p;  // distinct points in (x, y) order, and id = their index in pts
    vector<pair<int, int>> res;
    for (int i : ord) {
        if (!p.empty() && pts[i] == p.back()) res.push_back({id.back(), i});
        else p.push_back(pts[i]), id.push_back(i);
    }
    // quad-edge: edge e owns nodes 4e..4e+3 (e, rot, sym, rot of sym); nxt = onext, org = origin of primal nodes
    vector<int> nxt, org;
    vector<char> dead;
    auto rot = [](int e) { return (e & ~3) | ((e + 1) & 3); };
    auto rotinv = [](int e) { return (e & ~3) | ((e + 3) & 3); };
    auto sym = [](int e) { return e ^ 2; };
    auto oprev = [&](int e) { return rot(nxt[rot(e)]); };
    auto lnext = [&](int e) { return rot(nxt[rotinv(e)]); };
    auto dest = [&](int e) { return org[e ^ 2]; };
    auto make_edge = [&](int a, int b) {
        int e = nxt.size();
        nxt.insert(nxt.end(), {e, e + 3, e + 2, e + 1});
        org.insert(org.end(), {a, -1, b, -1});
        dead.push_back(0);
        return e;
    };
    auto splice = [&](int a, int b) {
        int x = rot(nxt[a]), y = rot(nxt[b]);
        swap(nxt[a], nxt[b]);
        swap(nxt[x], nxt[y]);
    };
    auto connect = [&](int a, int b) {  // new edge from dest(a) to org(b), with a, e, b sharing a left face
        int e = make_edge(dest(a), org[b]);
        splice(e, lnext(a));
        splice(sym(e), b);
        return e;
    };
    auto remove = [&](int e) {
        splice(e, oprev(e));
        splice(sym(e), oprev(sym(e)));
        dead[e >> 2] = 1;
    };
    auto ccw = [&](int a, int b, int c) {
        return (__int128)(p[b].first - p[a].first) * (p[c].second - p[a].second) -
               (__int128)(p[b].second - p[a].second) * (p[c].first - p[a].first) > 0;
    };
    auto in_circle = [&](int a, int b, int c, int d) {  // d strictly inside the circle through ccw a, b, c
        __int128 m[3][3];
        int q[3] = {a, b, c};
        for (int i = 0; i < 3; i++) {
            __int128 x = p[q[i]].first - p[d].first, y = p[q[i]].second - p[d].second;
            m[i][0] = x, m[i][1] = y, m[i][2] = x * x + y * y;
        }
        return m[0][0] * (m[1][1] * m[2][2] - m[1][2] * m[2][1]) - m[0][1] * (m[1][0] * m[2][2] - m[1][2] * m[2][0]) +
               m[0][2] * (m[1][0] * m[2][1] - m[1][1] * m[2][0]) > 0;
    };
    auto right_of = [&](int x, int e) { return ccw(x, dest(e), org[e]); };
    auto left_of = [&](int x, int e) { return ccw(x, org[e], dest(e)); };
    // triangulates p[l, r), returns {ccw hull edge out of the leftmost point, cw hull edge out of the rightmost}
    auto rec = [&](auto &self, int l, int r) -> pair<int, int> {
        if (r - l == 2) {
            int a = make_edge(l, l + 1);
            return {a, sym(a)};
        }
        if (r - l == 3) {
            int a = make_edge(l, l + 1), b = make_edge(l + 1, l + 2);
            splice(sym(a), b);
            if (ccw(l, l + 1, l + 2)) {
                connect(b, a);
                return {a, sym(b)};
            }
            if (ccw(l, l + 2, l + 1)) {
                int c = connect(b, a);
                return {sym(c), c};
            }
            return {a, sym(b)};  // collinear
        }
        int mid = (l + r) / 2;
        auto [ldo, ldi] = self(self, l, mid);
        auto [rdi, rdo] = self(self, mid, r);
        while (true) {  // lower common tangent of the two halves
            if (left_of(org[rdi], ldi)) ldi = lnext(ldi);
            else if (right_of(org[ldi], rdi)) rdi = nxt[sym(rdi)];
            else break;
        }
        int base = connect(sym(rdi), ldi);
        if (org[ldi] == org[ldo]) ldo = sym(base);
        if (org[rdi] == org[rdo]) rdo = base;
        auto valid = [&](int e) { return right_of(dest(e), base); };
        while (true) {  // zip the halves together upward, deleting edges that fail the empty-circle test
            int lc = nxt[sym(base)], rc = oprev(base);
            if (valid(lc)) {
                while (in_circle(dest(base), org[base], dest(lc), dest(nxt[lc]))) {
                    int t = nxt[lc];
                    remove(lc);
                    lc = t;
                }
            }
            if (valid(rc)) {
                while (in_circle(dest(base), org[base], dest(rc), dest(oprev(rc)))) {
                    int t = oprev(rc);
                    remove(rc);
                    rc = t;
                }
            }
            bool vl = valid(lc), vr = valid(rc);
            if (!vl && !vr) break;
            if (!vl || (vr && in_circle(dest(lc), org[lc], org[rc], dest(rc)))) base = connect(rc, sym(base));
            else base = connect(sym(base), sym(lc));
        }
        return {ldo, rdo};
    };
    if (p.size() >= 2) rec(rec, 0, p.size());
    for (int e = 0; e < (int)dead.size(); e++) if (!dead[e]) res.push_back({id[org[4 * e]], id[org[4 * e + 2]]});
    return res;
}

void solve() {
    ll n;
    cin >> n;
    vector<pll> p(n);
    for (ll i = 0; i < n; i++) cin >> p[i].first >> p[i].second;
    vector<array<ll, 3>> edges;
    for (auto [u, v] : delaunay_edges(p)) {
        ll dx = p[u].first - p[v].first, dy = p[u].second - p[v].second;
        edges.push_back({dx * dx + dy * dy, u, v});
    }
    auto [w, chosen] = kruskal(n, edges);
    for (int i : chosen) cout << edges[i][1] << " " << edges[i][2] << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(20);

    int t = 1;
    // cin >> t;  // comment out for single test
    while (t--) solve();
}
