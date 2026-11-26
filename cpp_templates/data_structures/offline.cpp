// Contents
//   binexp                a^b mod mod, O(log b)
//   hilbert_order         position of (x, y) along a Hilbert curve of order pow; requires x, y < 2^pow, O(pow)
//   mo                    Mo's algorithm with Hilbert ordering; queries are {l, r} over [l, r)
//   range_inversions      number of inversions in each a[l, r), using mo above and a Fenwick tree
//   binomial_prefix_sums  sum of C(n, i) over i <= k for each query {n, k}, Mo's algorithm on the points (n, k)
//   cdq_dominance         offline 2D dominance sums with point updates (CDQ divide and conquer), O(n log^2 n)
//   mo_updates            Mo's algorithm with point updates; queries are {l, r, t} over [l, r) after t updates,
//                         O(n^(5/3))
//   mo_tree               Mo's algorithm on tree paths; queries are {u, v}, over the vertices of the path u - v

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;

// a^b mod mod, O(log b)
ll binexp(ll a, ll b, ll mod) {
    ll ans = 1;
    a %= mod;
    while (b) {
        if (b & 1) ans = ans * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return ans;
}

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

// sum of C(n, i) over 0 <= i <= k for each query {n, k} (n, k >= 0), mod a prime mod > max n; Mo's algorithm over the
// points (n, k) in Hilbert order, using binexp and hilbert_order above: S(n, k) - S(n, k - 1) = C(n, k) and
// S(n + 1, k) = 2 S(n, k) - C(n, k), O(max(n, k) sqrt q) steps
vector<ll> binomial_prefix_sums(const vector<pair<int, int>> &queries, ll mod) {
    int q = queries.size(), N = 1, pow = 0;
    for (auto [n, k] : queries) N = max({N, n + 1, k + 1});
    while ((1 << pow) < N) pow++;
    vector<ll> fac(N + 1, 1), ifac(N + 1, 1), key(q), ans(q);
    for (int i = 1; i <= N; i++) fac[i] = fac[i - 1] * i % mod;
    ifac[N] = binexp(fac[N], mod - 2, mod);
    for (int i = N; i > 0; i--) ifac[i - 1] = ifac[i] * i % mod;
    auto C = [&](int n, int k) { return k > n ? 0 : fac[n] * ifac[k] % mod * ifac[n - k] % mod; };
    vector<int> order(q);
    for (int i = 0; i < q; i++) key[i] = hilbert_order(queries[i].first, queries[i].second, pow), order[i] = i;
    sort(order.begin(), order.end(), [&](int a, int b) { return key[a] < key[b]; });
    ll S = 1, half = (mod + 1) / 2;  // S = S(n, k)
    int n = 0, k = 0;
    for (int i : order) {
        auto [qn, qk] = queries[i];
        while (n < qn) S = (2 * S - C(n, k) + mod) % mod, n++;
        while (k > qk) S = (S - C(n, k) + mod) % mod, k--;
        while (n > qn) n--, S = (S + C(n, k)) * half % mod;
        while (k < qk) k++, S = (S + C(n, k)) % mod;
        ans[i] = S;
    }
    return ans;
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

// Mo's algorithm with updates: query i is {l, r, t}, asking about [l, r) after the first t updates; add(i) /
// remove(i) change the window, toggle(j, l, r) applies update j if it is off and undoes it if it is on, given the
// current window [l, r) (an update that sets a[p] = x can be stored as {p, x} and toggled by swapping a[p] with x,
// removing and re-adding p if it lies in the window), get() returns the answer. Sorted by (l / B, r / B, t) with
// B ~ n^(2/3), O(n^(5/3)) calls when q and the number of updates are O(n)
template <class Add, class Remove, class Toggle, class Get>
auto mo_updates(int n, const vector<array<int, 3>> &queries, Add add, Remove remove, Toggle toggle, Get get) {
    int q = queries.size(), B = max(1, (int)cbrt((double)n * n));
    vector<int> order(q);
    iota(order.begin(), order.end(), 0);
    sort(order.begin(), order.end(), [&](int a, int b) {
        auto &x = queries[a], &y = queries[b];
        if (x[0] / B != y[0] / B) return x[0] < y[0];
        if (x[1] / B != y[1] / B) return (x[0] / B & 1) ? x[1] > y[1] : x[1] < y[1];
        return (x[1] / B & 1) ? x[2] > y[2] : x[2] < y[2];
    });
    vector<decltype(get())> ans(q);
    int l = 0, r = 0, t = 0;
    for (int i : order) {
        auto [ql, qr, qt] = queries[i];
        while (l > ql) add(--l);
        while (r < qr) add(r++);
        while (l < ql) remove(l++);
        while (r > qr) remove(--r);
        while (t < qt) toggle(t++, l, r);
        while (t > qt) toggle(--t, l, r);
        ans[i] = get();
    }
    return ans;
}

// Mo's algorithm on tree paths: query i is {u, v}, asking about the vertices on the path u - v (both included) of the
// tree adj; add(x) / remove(x) put vertex x in or take it out of the current set, get() returns the answer for it.
// Uses the Euler tour that lists each vertex on entry and exit: the path is the range between the two endpoints with
// the vertices seen twice dropped, plus the LCA when it is neither endpoint. Hilbert order via hilbert_order above,
// O((n + q) sqrt q) add/remove calls (plus O((n + q) log n) for the LCAs)
template <class Add, class Remove, class Get>
auto mo_tree(const vector<vector<int>> &adj, const vector<pair<int, int>> &queries, Add add, Remove remove, Get get,
             int root = 0) {
    int n = adj.size(), q = queries.size(), LOG = 1, T = 0, pow = 1;
    while ((1 << LOG) < n) LOG++;
    vector<int> tin(n), tout(n), tour(2 * n);
    vector<vector<int>> up(LOG + 1, vector<int>(n, root));
    vector<pair<int, int>> st{{root, root}};  // {vertex, parent}; a vertex is pushed again as ~v to mark its exit
    while (!st.empty()) {
        auto [v, p] = st.back();
        st.pop_back();
        if (v < 0) {
            tour[tout[~v] = T++] = ~v;
            continue;
        }
        up[0][v] = p;
        tour[tin[v] = T++] = v;
        st.push_back({~v, p});
        for (int w : adj[v]) if (w != p) st.push_back({w, v});
    }
    for (int j = 1; j <= LOG; j++) for (int v = 0; v < n; v++) up[j][v] = up[j - 1][up[j - 1][v]];
    auto is_anc = [&](int a, int b) { return tin[a] <= tin[b] && tout[b] <= tout[a]; };
    auto lca = [&](int a, int b) {
        if (is_anc(a, b)) return a;
        for (int j = LOG; j >= 0; j--) if (!is_anc(up[j][a], b)) a = up[j][a];
        return up[0][a];
    };
    vector<int> ql(q), qr(q), extra(q, -1), order(q);
    vector<ll> key(q);
    while ((1 << pow) <= 2 * n) pow++;
    for (int i = 0; i < q; i++) {
        auto [u, v] = queries[i];
        if (tin[u] > tin[v]) swap(u, v);
        int w = lca(u, v);
        if (w == u) ql[i] = tin[u], qr[i] = tin[v] + 1;
        else ql[i] = tout[u], qr[i] = tin[v] + 1, extra[i] = w;
        key[i] = hilbert_order(ql[i], qr[i], pow), order[i] = i;
    }
    sort(order.begin(), order.end(), [&](int a, int b) { return key[a] < key[b]; });
    vector<char> in(n);
    auto flip = [&](int x) {
        if ((in[x] ^= 1)) add(x);
        else remove(x);
    };
    vector<decltype(get())> ans(q);
    int l = 0, r = 0;
    for (int i : order) {
        while (l > ql[i]) flip(tour[--l]);
        while (r < qr[i]) flip(tour[r++]);
        while (l < ql[i]) flip(tour[l++]);
        while (r > qr[i]) flip(tour[--r]);
        if (extra[i] >= 0) add(extra[i]);
        ans[i] = get();
        if (extra[i] >= 0) remove(extra[i]);
    }
    return ans;
}
