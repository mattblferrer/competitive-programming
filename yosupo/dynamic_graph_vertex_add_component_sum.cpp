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
        }
        else {
            int mid = (lo + hi) / 2;
            solve(2 * k, lo, mid, f);
            solve(2 * k + 1, mid, hi, f);
        }
        ds.rollback(s);
    }
};

void solve() {
    ll n, q;
    cin >> n >> q;
    vector<ll> a(n);
    for (ll i = 0; i < n; i++) cin >> a[i];
    SumDSU ds(a);
    OfflineDynamic<SumDSU> od(q, ds);
    map<pll, ll> added;
    vector<ll> ask(q, -1);
    for (ll i = 0; i < q; i++) {
        ll t;
        cin >> t;
        if (t == 0) {
            ll u, v;
            cin >> u >> v;
            added[{min(u, v), max(u, v)}] = i;
        }
        else if (t == 1) {
            ll u, v;
            cin >> u >> v;
            auto it = added.find({min(u, v), max(u, v)});
            od.add(it->second, i, {0, u, v});
            added.erase(it);
        }
        else if (t == 2) {
            ll v, x;
            cin >> v >> x;
            od.add(i, q, {1, v, x});
        }
        else if (t == 3) {
            cin >> ask[i];
        }
    }
    for (auto [e, from] : added) od.add(from, q, {0, e.first, e.second});
    vector<ll> res(q);
    od.solve([&](int t) {
        if (ask[t] != -1) res[t] = ds.component_sum(ask[t]);
        });
    for (ll i = 0; i < q; i++) if (ask[i] != -1) cout << res[i] << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(20);

    int t = 1;
    // cin >> t;  // comment out for single test
    while (t--) solve();
}
