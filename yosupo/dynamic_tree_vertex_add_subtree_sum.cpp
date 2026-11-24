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

// link-cut tree: a forest under link and cut with path and subtree sum queries, 0-indexed; node values start at 0
// sum is over the splay subtree (a path); sub also counts vir, the sums of the virtual (non-preferred) children
//   LinkCutTree(n)    n isolated vertices, O(n)
//   make_root(x)      internal: make internal vertex x the root of its tree, O(log n) amortized
//   access(x)         internal: expose the root-to-x path, returns the last jump point, O(log n) amortized
//   connected(u, v)   true if u and v are in the same tree, O(log n) amortized
//   link(u, v)        add the edge u - v; false if they were already connected, O(log n) amortized
//   cut(u, v)         remove the edge u - v; false if it doesn't exist, O(log n) amortized
//   set(v, x)         set the value of v, O(log n) amortized
//   path_sum(u, v)    sum of the values on the path u - v; re-roots the tree at u; u and v must be connected, O(log n) amortized
//   subtree_sum(v, p) sum of the values in the subtree of v when the tree is rooted at p (p = v: the whole tree);
//                     re-roots the tree at p; v and p must be connected, O(log n) amortized
//   reroot(v)         make v the root of its tree, O(log n) amortized
//   lca(u, v)         lowest common ancestor for the current root; u and v must be connected, O(log n) amortized
struct LinkCutTree {
    struct Node {
        int ch[2] = {0, 0}, p = 0;
        ll val = 0, sum = 0, vir = 0, sub = 0;
        bool rev = false;
    };
    vector<Node> t;  // internal vertices are 1..n and 0 is null
    vector<int> path;

    LinkCutTree(int n = 0): t(n + 1) {}

    bool is_root(int x) const {
        int p = t[x].p;
        return !p || (t[p].ch[0] != x && t[p].ch[1] != x);
    }

    void pull(int x) {
        int l = t[x].ch[0], r = t[x].ch[1];
        t[x].sum = t[l].sum + t[x].val + t[r].sum;
        t[x].sub = t[l].sub + t[x].val + t[r].sub + t[x].vir;
    }

    void flip(int x) {
        if (!x) return;
        swap(t[x].ch[0], t[x].ch[1]);
        t[x].rev = !t[x].rev;
    }

    void push(int x) {
        if (!t[x].rev) return;
        flip(t[x].ch[0]);
        flip(t[x].ch[1]);
        t[x].rev = false;
    }

    void rotate(int x) {
        int p = t[x].p, g = t[p].p, d = t[p].ch[1] == x, c = t[x].ch[!d];
        if (!is_root(p)) t[g].ch[t[g].ch[1] == p] = x;
        t[x].p = g;
        t[p].ch[d] = c;
        if (c) t[c].p = p;
        t[x].ch[!d] = p;
        t[p].p = x;
        pull(p);
        pull(x);
    }

    void splay(int x) {
        path.clear();
        for (int y = x; ; y = t[y].p) {
            path.push_back(y);
            if (is_root(y)) break;
        }
        for (int i = (int)path.size() - 1; i >= 0; i--) push(path[i]);
        while (!is_root(x)) {
            int p = t[x].p, g = t[p].p;
            if (!is_root(p)) rotate((t[p].ch[1] == x) == (t[g].ch[1] == p) ? p : x);
            rotate(x);
        }
    }

    int access(int x) {
        int last = 0;
        for (int y = x; y; y = t[y].p) {
            splay(y);
            t[y].vir += t[t[y].ch[1]].sub - t[last].sub;  // the old preferred child becomes virtual
            t[y].ch[1] = last;
            pull(y);
            last = y;
        }
        splay(x);
        return last;
    }

    void make_root(int x) {
        access(x);
        flip(x);
    }

    int find_root(int x) {
        access(x);
        while (true) {
            push(x);
            if (!t[x].ch[0]) break;
            x = t[x].ch[0];
        }
        splay(x);
        return x;
    }

    bool connected(int u, int v) { return find_root(u + 1) == find_root(v + 1); }

    bool link(int u, int v) {
        if (connected(u, v)) return false;
        make_root(u + 1);
        access(v + 1);
        t[u + 1].p = v + 1;
        t[v + 1].vir += t[u + 1].sub;
        pull(v + 1);
        return true;
    }

    bool cut(int u, int v) {
        u++;
        v++;
        if (u == v || find_root(u) != find_root(v)) return false;
        make_root(u);
        access(v);
        push(u);
        if (t[v].ch[0] != u || t[u].ch[1]) return false;
        t[v].ch[0] = 0;
        t[u].p = 0;
        pull(v);
        return true;
    }

    void set(int v, ll x) {
        v++;
        access(v);
        t[v].val = x;
        pull(v);
    }

    ll path_sum(int u, int v) {
        make_root(u + 1);
        access(v + 1);
        return t[v + 1].sum;
    }

    ll subtree_sum(int v, int p) {
        make_root(p + 1);
        access(v + 1);
        return t[v + 1].val + t[v + 1].vir;
    }

    void reroot(int v) { make_root(v + 1); }

    int lca(int u, int v) {
        access(u + 1);
        return access(v + 1) - 1;
    }
};

void solve() {
    ll n, q;
    cin >> n >> q;
    vector<ll> a(n);
    LinkCutTree lct(n);
    for (ll i = 0; i < n; i++) {
        cin >> a[i];
        lct.set(i, a[i]);
    }
    for (ll i = 0; i < n - 1; i++) {
        ll u, v;
        cin >> u >> v;
        lct.link(u, v);
    }
    for (ll i = 0; i < q; i++) {
        ll t;
        cin >> t;
        if (t == 0) {
            ll u, v, w, x;
            cin >> u >> v >> w >> x;
            lct.cut(u, v);
            lct.link(w, x);
        }
        else if (t == 1) {
            ll p, x;
            cin >> p >> x;
            a[p] += x;
            lct.set(p, a[p]);
        }
        else if (t == 2) {
            ll v, p;
            cin >> v >> p;
            cout << lct.subtree_sum(v, p) << "\n";
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
