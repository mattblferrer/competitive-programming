#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;

// persistent segment tree, point add, range sum on [l, r); version 0 is all zeros or the built array
// each update makes a new version and leaves the old ones unchanged
//   PersistentSegTree(n)            version 0 is n zeros, O(1)
//   PersistentSegTree(a)            version 0 is a, O(n)
//   update(ver, p, v)               a[p] += v on a copy of ver, returns the new version, O(log n) time and memory
//   query(ver, l, r)                sum of a[l..r) in ver, O(log n)
struct PersistentSegTree {
    struct Node { int l, r; ll sum; };
    int n;
    vector<Node> t;  // t[0] is the empty node, whose children are itself
    vector<int> roots;

    PersistentSegTree(int n = 0): n(n), t(1, Node{0, 0, 0}), roots(1, 0) {}

    PersistentSegTree(const vector<ll> &a): PersistentSegTree((int)a.size()) {
        if (n) roots[0] = build(a, 0, n);
    }

    int build(const vector<ll> &a, int lo, int hi) {
        if (hi - lo == 1) {
            t.push_back({0, 0, a[lo]});
            return t.size() - 1;
        }
        int mid = (lo + hi) / 2;
        int l = build(a, lo, mid), r = build(a, mid, hi);
        t.push_back({l, r, t[l].sum + t[r].sum});
        return t.size() - 1;
    }

    int update(int ver, int p, ll v) {
        roots.push_back(update_node(roots[ver], 0, n, p, v));
        return roots.size() - 1;
    }

    int update_node(int x, int lo, int hi, int p, ll v) {
        Node cur = t[x];
        cur.sum += v;
        if (hi - lo > 1) {
            int mid = (lo + hi) / 2;
            if (p < mid) cur.l = update_node(cur.l, lo, mid, p, v);
            else cur.r = update_node(cur.r, mid, hi, p, v);
        }
        t.push_back(cur);
        return t.size() - 1;
    }

    ll query(int ver, int l, int r) const { return query_node(roots[ver], 0, n, l, r); }

    ll query_node(int x, int lo, int hi, int l, int r) const {
        if (!x || r <= lo || hi <= l) return 0;
        if (l <= lo && hi <= r) return t[x].sum;
        int mid = (lo + hi) / 2;
        return query_node(t[x].l, lo, mid, l, r) + query_node(t[x].r, mid, hi, l, r);
    }
};

// persistent lazy segment tree, range add, range sum on [l, r); version 0 is all zeros
// range adds are stored permanently on the nodes instead of being pushed down, so queries allocate nothing
//   PersistentLazySegTree(n)        version 0 is n zeros, O(1)
//   update(ver, l, r, v)            a[l..r) += v on a copy of ver, returns the new version, O(log n) time and memory
//   query(ver, l, r)                sum of a[l..r) in ver, O(log n)
struct PersistentLazySegTree {
    struct Node { int l, r; ll sum, add; };
    int n;
    vector<Node> t;  // t[0] is the empty node, whose children are itself
    vector<int> roots;

    PersistentLazySegTree(int n = 0): n(n), t(1, Node{0, 0, 0, 0}), roots(1, 0) {}

    int update(int ver, int l, int r, ll v) {
        roots.push_back(update_node(roots[ver], 0, n, l, r, v));
        return roots.size() - 1;
    }

    int update_node(int x, int lo, int hi, int l, int r, ll v) {
        Node cur = t[x];
        cur.sum += v * (min(hi, r) - max(lo, l));
        if (l <= lo && hi <= r) {
            cur.add += v;
        } else {
            int mid = (lo + hi) / 2;
            if (l < mid) cur.l = update_node(cur.l, lo, mid, l, r, v);
            if (mid < r) cur.r = update_node(cur.r, mid, hi, l, r, v);
        }
        t.push_back(cur);
        return t.size() - 1;
    }

    ll query(int ver, int l, int r) const { return query_node(roots[ver], 0, n, l, r); }

    ll query_node(int x, int lo, int hi, int l, int r) const {
        if (!x) return 0;
        if (l <= lo && hi <= r) return t[x].sum;
        ll res = t[x].add * (min(hi, r) - max(lo, l));
        int mid = (lo + hi) / 2;
        if (l < mid) res += query_node(t[x].l, lo, mid, l, r);
        if (mid < r) res += query_node(t[x].r, mid, hi, l, r);
        return res;
    }
};

// counts values <= x in any subarray, online; values can be any integers
//   LeqCounter(a)      build from a, O(n log n)
//   count(l, r, x)     number of i in [l, r) with a[i] <= x, O(log n)
struct LeqCounter {
    vector<ll> sorted_vals;
    PersistentSegTree tree;

    LeqCounter(const vector<ll> &a): tree((int)a.size()) {
        int n = a.size();
        vector<int> order(n);
        iota(order.begin(), order.end(), 0);
        sort(order.begin(), order.end(), [&](int i, int j) { return a[i] < a[j]; });
        for (int i : order) {
            sorted_vals.push_back(a[i]);
            tree.update(tree.roots.size() - 1, i, 1);
        }
    }

    int count(int l, int r, ll x) const {
        int ver = upper_bound(sorted_vals.begin(), sorted_vals.end(), x) - sorted_vals.begin();
        return tree.query(ver, l, r);
    }
};

// counts distinct values in any subarray, online; uses LeqCounter above
//   UniqueCounter(a)    build from a, O(n log n)
//   count(l, r)         number of distinct values in a[l..r), O(log n)
struct UniqueCounter {
    LeqCounter counter;

    static vector<ll> previous(const vector<ll> &a) {  // 1-indexed position of the previous equal value, 0 if none
        map<ll, int> last;
        vector<ll> b(a.size());
        for (int i = 0; i < (int)a.size(); i++) {
            b[i] = last[a[i]];
            last[a[i]] = i + 1;
        }
        return b;
    }

    UniqueCounter(const vector<ll> &a): counter(previous(a)) {}

    int count(int l, int r) const { return counter.count(l, r, l); }  // a[i] is new if its previous copy is before l
};
