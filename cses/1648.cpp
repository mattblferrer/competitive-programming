#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

struct point_segtree {
    int n;
    ll *vals;
    point_segtree(vector<ll> &ar, int n) {
        this->n = n;
        vals = new ll[2 * n];
        for (int i = 0; i < n; ++i) vals[i + n] = ar[i];
        for (int i = n - 1; i > 0; --i) vals[i] = vals[i << 1] + vals[(i << 1) | 1];
    }
    void update(int i, ll v) {
        for (vals[i += n] = v; i > 1; i >>= 1)
            vals[i >> 1] = vals[i] + vals[i ^ 1];
    }
    ll query(int l, int r) {
        ll res = 0;
        for (l += n, r += n + 1; l < r; l >>= 1, r >>= 1) {
            if (l & 1) res += vals[l++];
            if (r & 1) res += vals[--r];
        }
        return res;
    }
};

void solve() {
    ll n, q;
    cin >> n >> q;
    vector<ll> x(n + 1);
    for (ll i = 1; i <= n; i++) cin >> x[i];
    point_segtree tree(x, n + 1);
    for (ll i = 0; i < q; i++) {
        ll type;
        cin >> type;
        if (type == 1) {
            ll k, u;
            cin >> k >> u;
            tree.update(k, u);
        }
        else if (type == 2) {
            ll a, b;
            cin >> a >> b;
            cout << tree.query(a, b) << "\n";
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