#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1'000'000'007;

struct range_segtree {
    ll i, j, val, temp_val = 0;
    range_segtree *l, *r;
    range_segtree(vector<ll> &ar, int _i, int _j): i(_i), j(_j) {
        if (i == j) {
            val = ar[i];
            l = r = NULL;
        }
        else {
            int k = (i + j) >> 1;
            l = new range_segtree(ar, i, k);
            r = new range_segtree(ar, k + 1, j);
            val = max(0LL, l->val) + max(0LL, r->val);
        }
    }
    void visit() {
        if (temp_val) {
            val += (j - i + 1) * temp_val;
            if (l) {
                l->temp_val += temp_val;
                r->temp_val += temp_val;
            }
            temp_val = 0;
        }
    }
    void increase(int _i, int _j, ll _inc) {
        visit();
        if (_i <= i && j <= _j) {
            temp_val += _inc;
            visit();
        }
        else if (_j < i or j < _i) {
            // do nothing
        }
        else {
            l->increase(_i, _j, _inc);
            r->increase(_i, _j, _inc);
            val = max(0LL, l->val) + max(0LL, r->val);
        }
    }
    ll query(int _i, int _j) {
        visit();
        if (_i <= i and j <= _j) return max(0LL, val);
        else if (_j < i || j < _i) return 0;
        else return max(0LL, l->query(_i, _j)) + max(0LL, r->query(_i, _j));
    }
};

void solve() {
    ll n;
    cin >> n;
    vector<ll> a(n);
    for (ll i = 0; i < n; i++) cin >> a[i];

    vector<ll> ans(n);
    range_segtree tree(ans, 0, n - 1), unknown(ans, 0, n - 1);
    for (ll i = 0; i < n; i++) {
        if (a[i] <= 0) tree.increase(i, i, 1);
        if (a[i] == -1) unknown.increase(i, i, 1);
    }
    for (ll i = 0; i < n; i++) {
        if (a[i] > 0) {
            if (tree.query(i - a[i] + 1, i + a[i] - 1) > unknown.query(i - a[i] + 1, i + a[i] - 1)) {
                cout << "-1\n";
                return;
            }
            tree.increase(i - a[i] + 1, i + a[i] - 1, -1);
            unknown.increase(i - a[i] + 1, i + a[i] - 1, -1);
        }
    }
    if (tree.query(0, n - 1) == 0) {
        cout << "-1\n";
        return;
    }

    for (ll i = 0; i < n; i++) {
        ans[i] = tree.query(i, i);
    }
    for (ll i = 0; i < n; i++) {
        if (a[i] > 0) {
            ll tr = 0;
            if (i - a[i] >= 0) tr += ans[i - a[i]];
            if (i + a[i] < n) tr += ans[i + a[i]];
            if (tr == 0) {
                cout << "-1\n";
                return;
            }
            if (tree.query(i - a[i] + 1, i + a[i] - 1) != 0) {
                cout << "-1\n";
                return;
            }
        }
    }
    for (ll i = 0; i < n; i++) cout << ans[i];
    cout << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    int t; cin >> t; while (t--) solve();
    return 0;
}