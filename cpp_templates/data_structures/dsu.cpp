// Contents
//   DSU              disjoint set union with path compression and union by size
//   PotentialDSU     DSU with potentials: value(u) - value(v) under constraints, for any additive group
//   PersistentArray  persistent array (path-copied segment tree), O(log n) get and set
//   PersistentDSU    persistent DSU: every merge makes a new version, O(log^2 n) per operation
//   RollbackDSU      DSU with undo, example structure for OfflineDynamic below; D needs Op, snapshot()
//   SumDSU           RollbackDSU with component sums and point adds, for OfflineDynamic
//   OfflineDynamic   segment tree over time

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;

// disjoint set union with path compression and union by size
//   DSU(n)               n singleton sets {0}, ..., {n - 1}, O(n)
//   find_set(a)          representative of a's set, O(alpha(n)) amortized
//   union_sets(a, b)     merge the sets of a and b; false if already in the same set, O(alpha(n))
//   is_connected(a, b)   whether a and b are in the same set, O(alpha(n))
struct DSU {
    vector<int> parent, sz;

    DSU(int n): parent(n), sz(n, 1) {
        iota(parent.begin(), parent.end(), 0);
    }

    int find_set(int a) {
        if (parent[a] == a) return a;
        return parent[a] = find_set(parent[a]);
    }

    bool union_sets(int a, int b) {
        a = find_set(a);
        b = find_set(b);
        if (a == b) return false;
        if (sz[a] < sz[b]) swap(a, b);
        parent[b] = a;
        sz[a] += sz[b];
        return true;
    }

    bool is_connected(int a, int b) { return find_set(a) == find_set(b); }
};

// DSU with potentials: keeps value(u) - value(v) for u, v in the same set, under constraints value(u) - value(v) = x
// T is any additive group (+, -, == and T() as zero): ll, ModInt, ...; union by size keeps find's recursion shallow
//   PotentialDSU(n)    n singleton sets, O(n)
//   find(v)            root of v's set, O(log n)
//   connected(u, v)    true if u and v are in the same set, O(log n)
//   diff(u, v)         value(u) - value(v); u and v must be connected, O(log n)
//   merge(u, v, x)     add the constraint value(u) - value(v) = x; false if it contradicts the others, O(log n)
template <class T>
struct PotentialDSU {
    vector<int> p, sz;
    vector<T> pot;  // pot[v] = value(v) - value(p[v])

    PotentialDSU(int n = 0): p(n), sz(n, 1), pot(n) { iota(p.begin(), p.end(), 0); }

    int find(int v) {
        if (p[v] == v) return v;
        int r = find(p[v]);
        pot[v] = pot[v] + pot[p[v]];
        p[v] = r;
        return r;
    }

    bool connected(int u, int v) { return find(u) == find(v); }

    T diff(int u, int v) {
        find(u);
        find(v);
        return pot[u] - pot[v];
    }

    bool merge(int u, int v, T x) {
        int ru = find(u), rv = find(v);
        if (ru == rv) return pot[u] - pot[v] == x;
        if (sz[ru] < sz[rv]) {
            p[ru] = rv;
            pot[ru] = x - pot[u] + pot[v];
            sz[rv] += sz[ru];
        } else {
            p[rv] = ru;
            pot[rv] = pot[u] - pot[v] - x;
            sz[ru] += sz[rv];
        }
        return true;
    }
};

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

// DSU with undo, example structure for OfflineDynamic below; D needs Op, snapshot(), apply(op), rollback(s)
//   RollbackDSU(n)     n singleton sets, O(n)
//   find_set(a)        root of a's set, O(log n)
//   connected(a, b)    true if a and b are in the same set, O(log n)
//   snapshot()         token for the current state, O(1)
//   apply(op)          union the two vertices of op, O(log n)
//   rollback(s)        undo every apply since snapshot s, O(changes)
struct RollbackDSU {
    using Op = pair<int, int>;
    vector<int> p;  // negative size at roots
    vector<pair<int, int>> changes;  // {index, old value}
    int comps;

    RollbackDSU(int n = 0): p(n, -1), comps(n) {}

    int find_set(int a) const {
        while (p[a] >= 0) a = p[a];
        return a;
    }

    bool connected(int a, int b) const { return find_set(a) == find_set(b); }

    int snapshot() const { return changes.size(); }

    void apply(const Op &op) {
        int a = find_set(op.first), b = find_set(op.second);
        if (a == b) return;
        if (p[a] > p[b]) swap(a, b);
        changes.push_back({a, p[a]});
        changes.push_back({b, p[b]});
        p[a] += p[b];
        p[b] = a;
        comps--;
    }

    void rollback(int s) {
        if ((int)changes.size() > s) comps += (changes.size() - s) / 2;
        while ((int)changes.size() > s) {
            p[changes.back().first] = changes.back().second;
            changes.pop_back();
        }
    }
};

// RollbackDSU above with a value per vertex and the sum of each component at its root, for OfflineDynamic
// ops are {0, u, v} (union u and v) and {1, v, x} (add x to the value of v)
//   SumDSU(a)            singleton sets with values a, O(n)
//   snapshot()           token for the current state, O(1)
//   apply(op)            apply one op, O(log n)
//   rollback(s)          undo every apply since snapshot s, O(changes)
//   component_sum(v)     sum of the values in v's set, O(log n)
struct SumDSU {
    using Op = array<ll, 3>;
    RollbackDSU dsu;
    vector<ll> sum;
    vector<pair<int, ll>> changes;  // {root, old sum}

    SumDSU(const vector<ll> &a): dsu(a.size()), sum(a) {}

    pair<int, int> snapshot() const { return {dsu.snapshot(), (int)changes.size()}; }

    void apply(const Op &op) {
        if (op[0] == 1) {
            int r = dsu.find_set(op[1]);
            changes.push_back({r, sum[r]});
            sum[r] += op[2];
            return;
        }
        int a = dsu.find_set(op[1]), b = dsu.find_set(op[2]);
        if (a == b) return;
        dsu.apply({a, b});
        int r = dsu.find_set(a);
        changes.push_back({r, sum[r]});
        sum[r] = sum[a] + sum[b];
    }

    void rollback(pair<int, int> s) {
        dsu.rollback(s.first);
        while ((int)changes.size() > s.second) {
            sum[changes.back().first] = changes.back().second;
            changes.pop_back();
        }
    }

    ll component_sum(int v) const { return sum[dsu.find_set(v)]; }
};

// segment tree over time: answer queries offline when operations are only active on time intervals
// k = number of operations added, T = cost of one D::apply
//   OfflineDynamic(n, ds)   n time points, O(n)
//   add(l, r, op)           op is active at times [l, r), O(log n)
//   solve(f)                call f(time) for every time with exactly the active ops applied, O(n + k T log n)
template <class D>
struct OfflineDynamic {
    int n;
    D &ds;
    vector<vector<typename D::Op>> t;

    OfflineDynamic(int n, D &ds): n(n), ds(ds), t(4 * max(n, 1)) {}

    void add(int l, int r, const typename D::Op &op) { add(1, 0, n, l, r, op); }

    void add(int k, int lo, int hi, int l, int r, const typename D::Op &op) {
        if (r <= lo || hi <= l) return;
        if (l <= lo && hi <= r) {
            t[k].push_back(op);
            return;
        }
        int mid = (lo + hi) / 2;
        add(2 * k, lo, mid, l, r, op);
        add(2 * k + 1, mid, hi, l, r, op);
    }

    template <class F>
    void solve(F f) { if (n > 0) solve(1, 0, n, f); }

    template <class F>
    void solve(int k, int lo, int hi, F &f) {
        auto s = ds.snapshot();
        for (auto &op : t[k]) ds.apply(op);
        if (hi - lo == 1) {
            f(lo);
        } else {
            int mid = (lo + hi) / 2;
            solve(2 * k, lo, mid, f);
            solve(2 * k + 1, mid, hi, f);
        }
        ds.rollback(s);
    }
};
