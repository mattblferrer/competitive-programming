#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

struct segtree_2d {
    int n, m;
    ll **ar;
    segtree_2d(int n, int m) {
        this->n = n;
        this->m = m;
        ar = new ll * [2 * n];
        for (int i = 0; i < 2 * n; ++i) {
            ar[i] = new ll[2 * m];
            for (int j = 0; j < 2 * m; ++j) ar[i][j] = 0;
        }
    }
    void update(int r, int c, ll v) {
        ar[r + n][c + m] = v;
        for (int i = r + n; i > 0; i >>= 1) {
            for (int j = c + m; j > 0; j >>= 1) {
                ar[i >> 1][j] = ar[i][j] + ar[i ^ 1][j];
                ar[i][j >> 1] = ar[i][j] + ar[i][j ^ 1];
            }
        }
    }
    ll query(int r1, int r2, int c1, int c2) {
        ll s = 0;
        if (~r2) {
            for (int a = r1 + n, b = r2 + n + 1; a < b; a >>= 1, b >>= 1) {
                if (a & 1) s += query(a++, -1, c1, c2);
                if (b & 1) s += query(--b, -1, c1, c2);
            }
        }
        else {
            for (int a = c1 + m, b = c2 + m + 1; a < b; a >>= 1, b >>= 1) {
                if (a & 1) s += ar[r1][a++];
                if (b & 1) s += ar[r1][--b];
            }
        }
        return s;
    }
};

void solve() {
    ll n, q;
    cin >> n >> q;
    vector<string> forest_str(n);
    for (ll i = 0; i < n; i++) {
        cin >> forest_str[i];
    }
    segtree_2d forest(n, n);
    for (ll i = 0; i < n; i++) {
        for (ll j = 0; j < n; j++) {
            if (forest_str[i][j] == '*') forest.update(i, j, 1);
        }
    }
    for (ll i = 0; i < q; i++) {
        ll x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        x1--; y1--; x2--; y2--;
        cout << forest.query(x1, x2, y1, y2) << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}