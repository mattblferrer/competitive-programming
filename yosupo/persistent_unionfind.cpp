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

// persistent array: a version is the root of a path-copied segment tree, so set leaves every old version unchanged
//   PersistentArray(a)   version root holds a; n must be positive, O(n)
//   get(ver, p)          a[p] in ver, O(log n)
//   set(ver, p, v)       a copy of ver with a[p] = v, returns the new version, O(log n) time and memory
template <class T>
struct PersistentArray {
    struct Node { int l, r; T val; };
    int n, root;
    vector<Node> t;

    PersistentArray(const vector<T> &a): n(a.size()) { root = n ? build(a, 0, n) : 0; }

    int build(const vector<T> &a, int lo, int hi) {
        if (hi - lo == 1) {
            t.push_back({0, 0, a[lo]});
            return t.size() - 1;
        }
        int mid = (lo + hi) / 2, l = build(a, lo, mid), r = build(a, mid, hi);
        t.push_back({l, r, T()});
        return t.size() - 1;
    }

    T get(int ver, int p) const {
        for (int lo = 0, hi = n; hi - lo > 1;) {
            int mid = (lo + hi) / 2;
            if (p < mid) ver = t[ver].l, hi = mid;
            else ver = t[ver].r, lo = mid;
        }
        return t[ver].val;
    }

    int set(int ver, int p, const T &v) { return set(ver, 0, n, p, v); }

    int set(int x, int lo, int hi, int p, const T &v) {
        Node cur = t[x];
        if (hi - lo == 1) cur.val = v;
        else {
            int mid = (lo + hi) / 2;
            if (p < mid) cur.l = set(cur.l, lo, mid, p, v);
            else cur.r = set(cur.r, mid, hi, p, v);
        }
        t.push_back(cur);
        return t.size() - 1;
    }
};

// persistent DSU: union by size without path compression, on PersistentArray above; version 0 is n singletons
// every merge makes a new version (even when a and b are already connected) and leaves the old ones unchanged
//   PersistentDSU(n)        n singleton sets, O(n)
//   find(ver, a)            root of a's set in ver, O(log^2 n)
//   connected(ver, a, b)    true if a and b are in the same set in ver, O(log^2 n)
//   size(ver, a)            size of a's set in ver, O(log^2 n)
//   merge(ver, a, b)        a copy of ver with the sets of a and b merged, returns the new version, O(log^2 n) time,
//                           O(log n) memory
struct PersistentDSU {
    PersistentArray<int> p;  // negative size at roots
    vector<int> roots;

    PersistentDSU(int n): p(vector<int>(n, -1)), roots{p.root} {}

    int find(int ver, int a) const {
        for (int x; (x = p.get(roots[ver], a)) >= 0;) a = x;
        return a;
    }

    bool connected(int ver, int a, int b) const { return find(ver, a) == find(ver, b); }
    int size(int ver, int a) const { return -p.get(roots[ver], find(ver, a)); }

    int merge(int ver, int a, int b) {
        int r = roots[ver];
        a = find(ver, a), b = find(ver, b);
        if (a != b) {
            int sa = p.get(r, a), sb = p.get(r, b);
            if (sa > sb) swap(a, b), swap(sa, sb);
            r = p.set(p.set(r, a, sa + sb), b, a);
        }
        roots.push_back(r);
        return roots.size() - 1;
    }
};

void solve() {
    ll n, q;
    cin >> n >> q;
    PersistentDSU dsu(n);
    vector<int> ver(q + 1, 0);
    for (ll i = 0; i < q; i++) {
        ll type, k, u, v;
        cin >> type >> k >> u >> v;
        if (type == 0) ver[i + 1] = dsu.merge(ver[k + 1], u, v);
        if (type == 1) {
            cout << dsu.connected(ver[k + 1], u, v) << "\n";
            ver[i + 1] = ver[k + 1];
        }
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
