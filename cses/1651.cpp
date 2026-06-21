#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

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
            val = l->val + r->val;
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
            val = l->val + r->val;
        }
    }
    ll query(int _i, int _j) {
        visit();
        if (_i <= i and j <= _j) return val;
        else if (_j < i || j < _i) return 0;
        else return l->query(_i, _j) + r->query(_i, _j);
    }
};

void solve() {
    ll n, q;
    cin >> n >> q;
    vector<ll> x(n + 1);
    for (ll i = 1; i <= n; i++) cin >> x[i];
    range_segtree tree(x, 1, n + 1);
    for (ll i = 0; i < q; i++) {
        ll type;
        cin >> type;
        if (type == 1) {
            ll a, b, u;
            cin >> a >> b >> u;
            tree.increase(a, b, u);
        }
        else if (type == 2) {
            ll k;
            cin >> k;
            cout << tree.query(k, k) << "\n";
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