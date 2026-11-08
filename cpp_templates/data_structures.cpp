#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;

// set with order statistics: s.find_by_order(k) (0-indexed iterator), s.order_of_key(x) (# of elements < x), O(log n)
// use IndexedSet<pair<T, int>> for a multiset
template <class T>
using IndexedSet = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

// coordinate compression
//   Compressor(a)   sorted distinct values of a, O(n log n)
//   id(x)           index of x, or of the first value above x if x is absent, O(log n)
//   val(i)          the i-th smallest distinct value, O(1)
//   size()          number of distinct values, O(1)
template <class T>
struct Compressor {
    vector<T> v;

    Compressor(vector<T> a = {}): v(move(a)) {
        sort(v.begin(), v.end());
        v.erase(unique(v.begin(), v.end()), v.end());
    }

    int id(const T &x) const { return lower_bound(v.begin(), v.end(), x) - v.begin(); }
    T val(int i) const { return v[i]; }
    int size() const { return v.size(); }
};

// Fenwick tree (0-indexed)
//   Fenwick(n)          n zeros, O(n)
//   Fenwick(a)           build from a, O(n)
//   add(i, v)            a[i] += v, O(log n)
//   sum(r)               sum of a[0..r), O(log n)
//   sum(l, r)            sum of a[l..r), O(log n)
//   get(i)               a[i], O(log n)
//   set(i, v)            a[i] = v, O(log n)
//   lower_bound(s)       smallest p with sum(p + 1) >= s, n if none; requires a[i] >= 0, O(log n)
struct Fenwick {
    int n;
    vector<ll> t;

    Fenwick(int n = 0): n(n), t(n + 1, 0) {}

    Fenwick(const vector<ll> &a): Fenwick((int)a.size()) {
        for (int i = 1; i <= n; i++) {
            t[i] += a[i - 1];
            int j = i + (i & -i);
            if (j <= n) t[j] += t[i];
        }
    }

    void add(int i, ll v) {
        for (i++; i <= n; i += i & -i) t[i] += v;
    }

    ll sum(int r) const {
        ll res = 0;
        for (; r > 0; r -= r & -r) res += t[r];
        return res;
    }

    ll sum(int l, int r) const { return sum(r) - sum(l); }

    ll get(int i) const { return sum(i, i + 1); }

    void set(int i, ll v) { add(i, v - get(i)); }

    int lower_bound(ll s) const {
        int p = 0;
        for (int k = n ? __lg(n) : 0; k >= 0 && n; k--) {
            if (p + (1 << k) <= n && t[p + (1 << k)] < s) {
                p += 1 << k;
                s -= t[p];
            }
        }
        return p;
    }
};

// Fenwick tree with range update, point query (0-indexed)
//   RangeFenwick(n)     n zeros, O(n)
//   add(l, r, v)        a[l..r) += v, O(log n)
//   get(i)              a[i], O(log n)
struct RangeFenwick {
    Fenwick f;

    RangeFenwick(int n = 0): f(n + 1) {}

    void add(int l, int r, ll v) {
        f.add(l, v);
        f.add(r, -v);
    }

    ll get(int i) const { return f.sum(i + 1); }
};

// stack with minimum query
//   empty()    true if the stack is empty, O(1)
//   push(x)    push x, O(1)
//   pop()      pop the top, O(1)
//   top()      top element, O(1)
//   min()      smallest element in the stack, O(1)
struct MinStack {
    vector<pll> st;  // {value, min up to here}

    bool empty() const { return st.empty(); }
    void push(ll x) { st.push_back({x, st.empty() ? x : std::min(x, st.back().second)}); }
    void pop() { st.pop_back(); }
    ll top() const { return st.back().first; }
    ll min() const { return st.back().second; }
};

// queue with minimum query
//   empty()    true if the queue is empty, O(1)
//   push(x)    push x at the back, O(1)
//   pop()      pop the front, O(1) amortized
//   front()    front element, O(1) amortized
//   min()      smallest element in the queue, O(1)
struct MinQueue {
    MinStack in, out;

    void flip() {
        if (!out.empty()) return;
        while (!in.empty()) {
            out.push(in.top());
            in.pop();
        }
    }

    bool empty() const { return in.empty() && out.empty(); }
    void push(ll x) { in.push(x); }
    void pop() { flip(); out.pop(); }
    ll front() { flip(); return out.top(); }

    ll min() const {
        if (in.empty()) return out.min();
        if (out.empty()) return in.min();
        return std::min(in.min(), out.min());
    }
};

// multiset of integers in [0, 2^BITS)
//   insert(x)    add one copy of x, O(BITS)
//   erase(x)     remove one copy of x; x must be present, O(BITS)
//   nth(k)       k-th smallest element (0-indexed); requires k < size, O(BITS)
template <int BITS = 20>
struct MisofTree {
    vector<vector<int>> cnt;

    MisofTree(): cnt(BITS) {
        for (int i = 0; i < BITS; i++) cnt[i].assign(1 << (BITS - i), 0);
    }

    void insert(int x) {
        for (int i = 0; i < BITS; i++, x >>= 1) cnt[i][x]++;
    }

    void erase(int x) {
        for (int i = 0; i < BITS; i++, x >>= 1) cnt[i][x]--;
    }

    int nth(int k) const {
        int res = 0;
        for (int i = BITS - 1; i >= 0; i--) {
            res <<= 1;
            if (cnt[i][res] <= k) {
                k -= cnt[i][res];
                res |= 1;
            }
        }
        return res;
    }
};

// position of (x, y) along a Hilbert curve of order pow; requires x, y < 2^pow, O(pow)
ll hilbert_order(int x, int y, int pow, int rotate = 0) {
    if (pow == 0) return 0;
    int h = 1 << (pow - 1);
    int seg = x < h ? (y < h ? 0 : 3) : (y < h ? 1 : 2);
    seg = (seg + rotate) & 3;
    static const int delta[4] = {3, 0, 0, 1};
    ll sub = 1LL << (2 * pow - 2);
    ll add = hilbert_order(x & (x ^ h), y & (y ^ h), pow - 1, (rotate + delta[seg]) & 3);
    return seg * sub + (seg == 1 || seg == 2 ? add : sub - add - 1);
}

// Mo's algorithm with Hilbert ordering; queries are {l, r} over [l, r), O((n + q) sqrt q) add/remove calls
// add(i) / remove(i) change the current window, get() returns the answer for it
template <class Add, class Remove, class Get>
auto mo(int n, const vector<pair<int, int>> &queries, Add add, Remove remove, Get get) {
    int q = queries.size(), pow = 1;
    while ((1 << pow) <= n) pow++;
    vector<ll> key(q);
    vector<int> order(q);
    for (int i = 0; i < q; i++) {
        key[i] = hilbert_order(queries[i].first, queries[i].second, pow);
        order[i] = i;
    }
    sort(order.begin(), order.end(), [&](int a, int b) { return key[a] < key[b]; });
    vector<decltype(get())> ans(q);
    int l = 0, r = 0;
    for (int i : order) {
        auto [ql, qr] = queries[i];
        while (l > ql) add(--l);  // grow before shrinking so the window never has negative length
        while (r < qr) add(r++);
        while (l < ql) remove(l++);
        while (r > qr) remove(--r);
        ans[i] = get();
    }
    return ans;
}

// sparse table; S must be idempotent, e.g. min, max, gcd, and shaped like MinOp
struct MinOp {
    using T = ll;
    static T op(const T &a, const T &b) { return min(a, b); }
};

// SparseTable<S>: static range query
//   SparseTable(a)   build from a, O(n log n)
//   query(l, r)      op over [l, r); requires l < r, O(1)
template <class S>
struct SparseTable {
    using T = typename S::T;
    vector<vector<T>> t;

    SparseTable(const vector<T> &a = {}): t(1, a) {
        int n = a.size();
        for (int j = 1; (1 << j) <= n; j++) {
            t.emplace_back(n - (1 << j) + 1);
            for (int i = 0; i + (1 << j) <= n; i++)
                t[j][i] = S::op(t[j - 1][i], t[j - 1][i + (1 << (j - 1))]);
        }
    }

    T query(int l, int r) const {
        int k = __lg(r - l);
        return S::op(t[k][l], t[k][r - (1 << k)]);
    }
};

// SparseTable2D<S>: static rectangle query, S as above
//   SparseTable2D(a)            build from grid a, O(nm log n log m)
//   query(r1, c1, r2, c2)       op over [r1, r2) x [c1, c2); requires r1 < r2 and c1 < c2, O(1)
template <class S>
struct SparseTable2D {
    using T = typename S::T;
    vector<vector<vector<vector<T>>>> t;  // t[a][b][i][j] covers [i, i + 2^a) x [j, j + 2^b)

    SparseTable2D(const vector<vector<T>> &g) {
        int n = g.size(), m = g[0].size(), la = __lg(n) + 1, lb = __lg(m) + 1;
        t.assign(la, vector<vector<vector<T>>>(lb, vector<vector<T>>(n, vector<T>(m))));
        for (int a = 0; a < la; a++) {
            for (int b = 0; b < lb; b++) {
                for (int i = 0; i + (1 << a) <= n; i++) {
                    for (int j = 0; j + (1 << b) <= m; j++) {
                        if (a == 0 && b == 0) t[a][b][i][j] = g[i][j];
                        else if (b > 0) t[a][b][i][j] = S::op(t[a][b - 1][i][j], t[a][b - 1][i][j + (1 << (b - 1))]);
                        else t[a][b][i][j] = S::op(t[a - 1][b][i][j], t[a - 1][b][i + (1 << (a - 1))][j]);
                    }
                }
            }
        }
    }

    T query(int r1, int c1, int r2, int c2) const {
        int a = __lg(r2 - r1), b = __lg(c2 - c1);
        return S::op(S::op(t[a][b][r1][c1], t[a][b][r1][c2 - (1 << b)]),
                     S::op(t[a][b][r2 - (1 << a)][c1], t[a][b][r2 - (1 << a)][c2 - (1 << b)]));
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

// implicit treap: an array supporting insert/erase at any position with range add and range sum (0-indexed)
//   insert(p, v)      insert v so that it becomes a[p], O(log n) expected
//   erase(p)          remove a[p], O(log n) expected
//   get(p)            a[p], O(log n) expected
//   query(l, r)       sum of a[l..r), O(log n) expected
//   update(l, r, v)   a[l..r) += v, O(log n) expected
//   size()            current length, O(1)
struct ImplicitTreap {
    struct Node {
        ll val, sum, add;
        unsigned pri;
        int sz, l, r;
    };
    vector<Node> t;  // t[0] is the null node
    int root = 0;
    mt19937 gen{(unsigned)chrono::steady_clock::now().time_since_epoch().count()};

    ImplicitTreap(): t(1, Node{0, 0, 0, 0, 0, 0, 0}) {}

    void apply(int v, ll d) {
        if (!v) return;
        t[v].val += d;
        t[v].add += d;
        t[v].sum += d * t[v].sz;
    }

    void push(int v) {
        apply(t[v].l, t[v].add);
        apply(t[v].r, t[v].add);
        t[v].add = 0;
    }

    void pull(int v) {
        t[v].sz = t[t[v].l].sz + 1 + t[t[v].r].sz;
        t[v].sum = t[t[v].l].sum + t[v].val + t[t[v].r].sum;
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

    void insert(int p, ll v) {
        t.push_back({v, v, 0, gen(), 1, 0, 0});
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

    ll get(int p) { return query(p, p + 1); }

    ll query(int l, int r) {
        int a, b, c;
        split(root, r, a, c);
        split(a, l, a, b);
        ll res = t[b].sum;
        root = merge(merge(a, b), c);
        return res;
    }

    void update(int l, int r, ll v) {
        int a, b, c;
        split(root, r, a, c);
        split(a, l, a, b);
        apply(b, v);
        root = merge(merge(a, b), c);
    }

    int size() const { return t[root].sz; }
};

// wavelet matrix: static order statistics on subarrays, online; values can be any integers
// B = number of bits needed for the distinct values, about log n
//   WaveletMatrix(a)      build from a, O(n log n)
//   kth(l, r, k)          k-th smallest value (0-indexed) in a[l..r); requires k < r - l, O(B)
//   count_less(l, r, x)   number of i in [l, r) with a[i] < x, O(B + log n)
//   count_eq(l, r, x)     number of i in [l, r) with a[i] == x, O(B + log n)
struct WaveletMatrix {
    int bits = 1;
    vector<ll> vals;
    vector<vector<int>> zeros;  // zeros[b][i] = number of the first i elements with this bit 0, at level b
    vector<int> mid;

    WaveletMatrix(const vector<ll> &a): vals(a) {
        sort(vals.begin(), vals.end());
        vals.erase(unique(vals.begin(), vals.end()), vals.end());
        while ((1LL << bits) < (ll)vals.size()) bits++;
        int n = a.size();
        vector<int> cur(n), left, right;
        for (int i = 0; i < n; i++) cur[i] = lower_bound(vals.begin(), vals.end(), a[i]) - vals.begin();
        zeros.assign(bits, vector<int>(n + 1, 0));
        mid.assign(bits, 0);
        for (int b = 0; b < bits; b++) {
            int bit = bits - 1 - b;
            left.clear();
            right.clear();
            for (int i = 0; i < n; i++) {
                bool one = cur[i] >> bit & 1;
                zeros[b][i + 1] = zeros[b][i] + !one;
                (one ? right : left).push_back(cur[i]);
            }
            mid[b] = left.size();
            cur = left;
            cur.insert(cur.end(), right.begin(), right.end());
        }
    }

    ll kth(int l, int r, int k) const {
        int res = 0;
        for (int b = 0; b < bits; b++) {
            int zl = zeros[b][l], zr = zeros[b][r];
            if (k < zr - zl) {
                l = zl;
                r = zr;
            } else {
                k -= zr - zl;
                res |= 1 << (bits - 1 - b);
                l = mid[b] + l - zl;
                r = mid[b] + r - zr;
            }
        }
        return vals[res];
    }

    int count_id_less(int l, int r, int id) const {  // id is a position in vals
        if (id >= (int)vals.size()) return r - l;
        int res = 0;
        for (int b = 0; b < bits; b++) {
            int zl = zeros[b][l], zr = zeros[b][r];
            if (id >> (bits - 1 - b) & 1) {
                res += zr - zl;
                l = mid[b] + l - zl;
                r = mid[b] + r - zr;
            } else {
                l = zl;
                r = zr;
            }
        }
        return res;
    }

    int count_less(int l, int r, ll x) const {
        return count_id_less(l, r, lower_bound(vals.begin(), vals.end(), x) - vals.begin());
    }

    int count_eq(int l, int r, ll x) const {
        int id = lower_bound(vals.begin(), vals.end(), x) - vals.begin();
        if (id == (int)vals.size() || vals[id] != x) return 0;
        return count_id_less(l, r, id + 1) - count_id_less(l, r, id);
    }
};
