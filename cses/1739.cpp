#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

struct Monoid {
    using T = ll;
    static T id() { return 0; }
    static T op(const T &a, const T &b) { return a + b; }
};

template <class M>
struct SegTree2D {
    using T = typename M::T;
    int n, m;
    vector<vector<T>> t;

    SegTree2D(int n = 0, int m = 0): n(n), m(m), t(2 * n, vector<T>(2 * m, M::id())) {}

    SegTree2D(const vector<vector<T>> &a): SegTree2D(a.size(), a.empty() ? 0 : a[0].size()) {
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++) t[n + i][m + j] = a[i][j];
        for (int i = n; i < 2 * n; i++)
            for (int j = m - 1; j > 0; j--) t[i][j] = M::op(t[i][2 * j], t[i][2 * j + 1]);
        for (int i = n - 1; i > 0; i--)
            for (int j = 1; j < 2 * m; j++) t[i][j] = M::op(t[2 * i][j], t[2 * i + 1][j]);
    }

    void set(int x, int y, T v) {
        x += n; y += m;
        t[x][y] = v;
        for (int j = y; j > 1; j >>= 1) t[x][j >> 1] = M::op(t[x][j & ~1], t[x][j | 1]);
        for (int i = x; i > 1; i >>= 1) {
            t[i >> 1][y] = M::op(t[i & ~1][y], t[i | 1][y]);
            for (int j = y; j > 1; j >>= 1)
                t[i >> 1][j >> 1] = M::op(t[i >> 1][j & ~1], t[i >> 1][j | 1]);
        }
    }

    T get(int x, int y) const { return t[x + n][y + m]; }

    T row_query(int i, int l, int r) const {
        T res = M::id();
        for (l += m, r += m; l < r; l >>= 1, r >>= 1) {
            if (l & 1) res = M::op(res, t[i][l++]);
            if (r & 1) res = M::op(res, t[i][--r]);
        }
        return res;
    }

    T query(int r1, int c1, int r2, int c2) const {
        T res = M::id();
        for (int i = r1 + n, k = r2 + 1 + n; i < k; i >>= 1, k >>= 1) {
            if (i & 1) res = M::op(res, row_query(i++, c1, c2 + 1));
            if (k & 1) res = M::op(res, row_query(--k, c1, c2 + 1));
        }
        return res;
    }
};

void solve() {
    ll n, q;
    cin >> n >> q;
    vector<string> forest_str(n);
    for (ll i = 0; i < n; i++) {
        cin >> forest_str[i];
    }
    SegTree2D<Monoid> forest(n, n);
    for (ll i = 0; i < n; i++) {
        for (ll j = 0; j < n; j++) {
            if (forest_str[i][j] == '*') forest.set(i, j, 1);
        }
    }
    for (ll i = 0; i < q; i++) {
        ll type;
        cin >> type;
        if (type == 1) {
            ll x, y;
            cin >> x >> y;
            x--; y--;
            forest.set(x, y, 1 - forest.get(x, y));
        }
        else if (type == 2) {
            ll x1, y1, x2, y2;
            cin >> x1 >> y1 >> x2 >> y2;
            x1--; y1--; x2--; y2--;
            cout << forest.query(x1, y1, x2, y2) << "\n";
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