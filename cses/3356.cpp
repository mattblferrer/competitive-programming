#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1'000'000'007;

struct Monoid {
    using T = ll;
    static T id() { return LLONG_MAX; }
    static T op(const T &a, const T &b) { return min(a, b); }
};

template <class M>
struct SegTree {
    using T = typename M::T;
    int n;
    vector<T> t;

    SegTree(int n = 0): n(n), t(2 * n, M::id()) {}

    SegTree(const vector<T> &a): n(a.size()), t(2 * a.size(), M::id()) {
        for (int i = 0; i < n; i++) t[n + i] = a[i];
        for (int i = n - 1; i > 0; i--) t[i] = M::op(t[2 * i], t[2 * i + 1]);
    }

    void set(int p, T v) {
        for (t[p += n] = v; p > 1; p >>= 1)
            t[p >> 1] = M::op(t[p & ~1], t[p | 1]);
    }

    T get(int p) const { return t[p + n]; }

    T query(int l, int r) const {
        T L = M::id(), R = M::id();
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l & 1) L = M::op(L, t[l++]);
            if (r & 1) R = M::op(t[--r], R);
        }
        return M::op(L, R);
    }
};

void solve() {
    ll n, q;
    cin >> n >> q;
    vector<ll> x(n + 1);
    map<ll, set<ll>> idx;
    for (ll i = 1; i <= n; i++) {
        cin >> x[i];
        idx[x[i]].insert(i);
    }

    vector<ll> nxt(n + 1, INF);
    for (ll i = 1; i <= n; i++) {
        auto it = idx[x[i]].upper_bound(i);
        if (it != idx[x[i]].end()) nxt[i] = *it;
    }
    SegTree<Monoid> tree(nxt);

    for (ll i = 1; i <= q; i++) {
        int type;
        cin >> type;
        if (type == 1) {
            ll k, u;
            cin >> k >> u;

            idx[x[k]].erase(k);
            auto it = idx[x[k]].lower_bound(k);
            if (it == idx[x[k]].begin()) {}
            else if (it == idx[x[k]].end()) tree.set(*prev(it), INF);
            else tree.set(*prev(it), *it);

            idx[u].insert(k);
            x[k] = u;
            auto it2 = idx[u].lower_bound(k);
            if ((it2 == idx[u].begin()) && (next(it2) == idx[u].end())) {
                tree.set(k, INF);
            }
            else if (it2 == idx[u].begin()) {
                tree.set(k, *next(it2));
            }
            else if (next(it2) == idx[u].end()) {
                tree.set(*prev(it2), k);
                tree.set(k, INF);
            }
            else {
                tree.set(*prev(it2), k);
                tree.set(k, *next(it2));
            }
        }
        else if (type == 2) {
            ll a, b;
            cin >> a >> b;
            if (tree.query(a, b + 1) > b) cout << "YES\n";
            else cout << "NO\n";
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}