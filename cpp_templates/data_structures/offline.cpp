// Contents
//   hilbert_order   position of (x, y) along a Hilbert curve of order pow; requires x, y < 2^pow, O(pow)
//   mo              Mo's algorithm with Hilbert ordering; queries are {l, r} over [l, r)

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
