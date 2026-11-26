// Contents
//   hilbert_order     position of (x, y) along a Hilbert curve of order pow; requires x, y < 2^pow, O(pow)
//   mo                Mo's algorithm with Hilbert ordering; queries are {l, r} over [l, r)
//   range_inversions  number of inversions in each a[l, r), using mo above and a Fenwick tree
//   cdq_dominance     offline 2D dominance sums with point updates (CDQ divide and conquer), O(n log^2 n)

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;

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

// number of inversions (i < j with a[i] > a[j]) in each a[l, r), queries are {l, r}; using mo above, with a Fenwick
// tree over the ranks of the window's values, O((n + q) sqrt q log n)
vector<ll> range_inversions(const vector<ll> &a, const vector<pair<int, int>> &queries) {
    int n = a.size(), l = 0, r = 0;  // mirrors mo's window [l, r), to tell whether i joins or leaves at the left end
    vector<ll> vals(a);
    sort(vals.begin(), vals.end());
    vector<int> rk(n), bit(n + 1);
    for (int i = 0; i < n; i++) rk[i] = lower_bound(vals.begin(), vals.end(), a[i]) - vals.begin();
    auto upd = [&](int i, int v) {
        for (i++; i <= n; i += i & -i) bit[i] += v;
    };
    auto below = [&](int x) {  // number of window values with rank < x
        int s = 0;
        for (; x > 0; x -= x & -x) s += bit[x];
        return s;
    };
    ll inv = 0;
    auto add = [&](int i) {
        if (l == r) l = r = i;  // emptied by a remove, which can't tell its end: either way it becomes [i, i + 1)
        if (i < l) inv += below(rk[i]), l = i;
        else inv += r - l - below(rk[i] + 1), r = i + 1;
        upd(rk[i], 1);
    };
    auto remove = [&](int i) {
        upd(rk[i], -1);
        if (i == l) inv -= below(rk[i]), l++;
        else inv -= r - 1 - l - below(rk[i] + 1), r--;
    };
    return mo(n, queries, add, remove, [&] { return inv; });
}

// offline 2D dominance sums with point updates, by CDQ divide and conquer over time: ops are in time order, an update
// {x, y, w, false} adds w at (x, y) and a query {x, y, 0, true} gets the sum of w over earlier updates with x' < x and
// y' < y (a rectangle is 4 such queries); returns each op's answer (0 for updates). The left half's updates are swept
// into the right half's queries in x order with a Fenwick tree over the y's, O(n log^2 n)
struct CDQOp {
    ll x, y, w;
    bool query;
};
vector<ll> cdq_dominance(const vector<CDQOp> &ops) {
    int n = ops.size();
    vector<ll> ys, ans(n);
    for (auto &o : ops) if (!o.query) ys.push_back(o.y);
    sort(ys.begin(), ys.end());
    ys.erase(unique(ys.begin(), ys.end()), ys.end());
    int m = ys.size();
    vector<int> yi(n), ord(n), tmp(n);  // yi = number of update y's below op's y, which is an update's y rank
    for (int i = 0; i < n; i++) yi[i] = lower_bound(ys.begin(), ys.end(), ops[i].y) - ys.begin(), ord[i] = i;
    vector<ll> bit(m + 1);
    auto upd = [&](int i, ll v) {
        for (i++; i <= m; i += i & -i) bit[i] += v;
    };
    auto pre = [&](int i) {
        ll s = 0;
        for (; i > 0; i -= i & -i) s += bit[i];
        return s;
    };
    auto solve = [&](auto &self, int l, int r) -> void {  // afterwards ord[l, r) is sorted by x
        if (r - l <= 1) return;
        int mid = (l + r) / 2, i = l;
        self(self, l, mid);
        self(self, mid, r);
        for (int j = mid; j < r; j++) {
            int b = ord[j];
            if (!ops[b].query) continue;
            for (; i < mid && ops[ord[i]].x < ops[b].x; i++) {
                if (!ops[ord[i]].query) upd(yi[ord[i]], ops[ord[i]].w);
            }
            ans[b] += pre(yi[b]);
        }
        for (int t = l; t < i; t++) if (!ops[ord[t]].query) upd(yi[ord[t]], -ops[ord[t]].w);
        merge(ord.begin() + l, ord.begin() + mid, ord.begin() + mid, ord.begin() + r, tmp.begin() + l,
              [&](int a, int b) { return ops[a].x < ops[b].x; });
        copy(tmp.begin() + l, tmp.begin() + r, ord.begin() + l);
        };
    solve(solve, 0, n);
    return ans;
}
