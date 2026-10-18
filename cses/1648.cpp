#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

struct Monoid {
    using T = long long;
    static T id() { return 0; }
    static T op(const T &a, const T &b) { return a + b; }
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
    for (ll i = 1; i <= n; i++) cin >> x[i];
    SegTree<Monoid> tree(x);
    for (ll i = 0; i < q; i++) {
        ll type;
        cin >> type;
        if (type == 1) {
            ll k, u;
            cin >> k >> u;
            tree.set(k, u);
        }
        else if (type == 2) {
            ll a, b;
            cin >> a >> b;
            cout << tree.query(a, b + 1) << "\n";
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