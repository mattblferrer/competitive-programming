#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

struct range_segtree {
    ll i, j, val, inc_val = 0, set_val = LLONG_MIN;
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
        if (inc_val) {
            val += (j - i + 1) * inc_val;
            if (l) {
                if (l->set_val != LLONG_MIN) l->set_val += inc_val;
                else l->inc_val += inc_val;
                if (r->set_val != LLONG_MIN) r->set_val += inc_val;
                else r->inc_val += inc_val;
            }
            inc_val = 0;
        }
        if (set_val != LLONG_MIN) {
            val = (j - i + 1) * set_val;
            if (l) {
                l->set_val = set_val;
                l->inc_val = 0;
                r->set_val = set_val;
                r->inc_val = 0;
            }
            set_val = LLONG_MIN;
        }
    }
    void increase(int _i, int _j, ll _inc) {
        visit();
        if (_i <= i && j <= _j) {
            inc_val += _inc;
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
    void set(int _i, int _j, ll v) {
        visit();
        if (_i <= i && j <= _j) {
            set_val = v;
            visit();
        }
        else if (_j < i or j < _i) {
            // do nothing
        }
        else {
            l->set(_i, _j, v);
            r->set(_i, _j, v);
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
    vector<ll> t(n + 1);
    for (ll i = 1; i <= n; i++) cin >> t[i];
    range_segtree tree(t, 1, n + 1);
    for (ll i = 0; i < q; i++) {
        ll type;
        cin >> type;
        if (type == 1) {
            ll a, b, x;
            cin >> a >> b >> x;
            tree.increase(a, b, x);
        }
        else if (type == 2) {
            ll a, b, x;
            cin >> a >> b >> x;
            tree.set(a, b, x);
        }
        else if (type == 3) {
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