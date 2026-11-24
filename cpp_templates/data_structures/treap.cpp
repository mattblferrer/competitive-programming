// Contents
//   ImplicitTreap   implicit treap over a lazy spec: insert/erase anywhere, range update, reverse and fold
//   IndexedSet      set with order statistics: s.find_by_order(k) (0-indexed iterator)

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;

// implicit treap: an array supporting insert/erase at any position, range update, range reverse and range fold
// (0-indexed); ImplicitTreap<S> takes a lazy spec S shaped like LazySegTree's (ready-made ones in monoids.cpp,
// and NoUpdate<M> there turns any monoid M into one); insert S::leaf(x) when apply needs the length
// each node keeps its subtree's fold in both directions, so reverse also works when op is not commutative
//   insert(p, v)      insert v so that it becomes a[p], O(log n) expected
//   erase(p)          remove a[p], O(log n) expected
//   get(p)            a[p], O(log n) expected
//   query(l, r)       op over a[l..r), O(log n) expected
//   update(l, r, f)   apply f to every element of a[l..r), O(log n) expected
//   reverse(l, r)     reverse a[l..r), O(log n) expected
//   size()            current length, O(1)
template <class S>
struct ImplicitTreap {
    using T = typename S::T;
    using F = typename S::F;
    struct Node {
        T val, sum, rsum;  // rsum = op over the subtree from right to left
        F lz;  // v's own val, sum, rsum already include lz; its children still need it
        unsigned pri;
        int sz, l, r;
        bool rev;  // v's own children are already swapped; rev means its children still need flipping
    };
    vector<Node> t;  // t[0] is the null node
    int root = 0;
    mt19937 gen{(unsigned)chrono::steady_clock::now().time_since_epoch().count()};

    ImplicitTreap(): t(1, Node{S::id(), S::id(), S::id(), S::fid(), 0, 0, 0, 0, false}) {}

    void apply(int v, const F &f) {
        if (!v) return;
        t[v].val = S::apply(f, t[v].val);
        t[v].sum = S::apply(f, t[v].sum);
        t[v].rsum = S::apply(f, t[v].rsum);
        t[v].lz = S::compose(f, t[v].lz);
    }

    void flip(int v) {
        if (!v) return;
        swap(t[v].l, t[v].r);
        swap(t[v].sum, t[v].rsum);
        t[v].rev = !t[v].rev;
    }

    void push(int v) {
        apply(t[v].l, t[v].lz);
        apply(t[v].r, t[v].lz);
        t[v].lz = S::fid();
        if (t[v].rev) {
            flip(t[v].l);
            flip(t[v].r);
            t[v].rev = false;
        }
    }

    void pull(int v) {
        int l = t[v].l, r = t[v].r;
        t[v].sz = t[l].sz + 1 + t[r].sz;
        t[v].sum = S::op(S::op(t[l].sum, t[v].val), t[r].sum);
        t[v].rsum = S::op(S::op(t[r].rsum, t[v].val), t[l].rsum);
    }

    int merge(int a, int b) {
        if (!a || !b) return a ? a : b;
        if (t[a].pri > t[b].pri) {
            push(a);
            t[a].r = merge(t[a].r, b);
            pull(a);
            return a;
        }
        push(b);
        t[b].l = merge(a, t[b].l);
        pull(b);
        return b;
    }

    // a gets the first k elements of v, b gets the rest
    void split(int v, int k, int &a, int &b) {
        if (!v) {
            a = b = 0;
            return;
        }
        push(v);
        if (k <= t[t[v].l].sz) {
            split(t[v].l, k, a, t[v].l);
            b = v;
        } else {
            split(t[v].r, k - t[t[v].l].sz - 1, t[v].r, b);
            a = v;
        }
        pull(v);
    }

    void insert(int p, const T &v) {
        t.push_back({v, v, v, S::fid(), gen(), 1, 0, 0, false});
        int a, b, id = t.size() - 1;
        split(root, p, a, b);
        root = merge(merge(a, id), b);
    }

    void erase(int p) {
        int a, b, c;
        split(root, p + 1, a, c);
        split(a, p, a, b);
        root = merge(a, c);
    }

    T get(int p) {
        int v = root;
        while (true) {
            push(v);
            int left = t[t[v].l].sz;
            if (p < left) {
                v = t[v].l;
            } else if (p == left) {
                return t[v].val;
            } else {
                p -= left + 1;
                v = t[v].r;
            }
        }
    }

    T query(int l, int r) {
        int a, b, c;
        split(root, r, a, c);
        split(a, l, a, b);
        T res = t[b].sum;
        root = merge(merge(a, b), c);
        return res;
    }

    void update(int l, int r, const F &f) {
        int a, b, c;
        split(root, r, a, c);
        split(a, l, a, b);
        apply(b, f);
        root = merge(merge(a, b), c);
    }

    void reverse(int l, int r) {
        int a, b, c;
        split(root, r, a, c);
        split(a, l, a, b);
        flip(b);
        root = merge(merge(a, b), c);
    }

    int size() const { return t[root].sz; }
};

// set with order statistics: s.find_by_order(k) (0-indexed iterator), s.order_of_key(x) (# of elements < x), O(log n)
// use IndexedSet<pair<T, int>> for a multiset
template <class T>
using IndexedSet = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
