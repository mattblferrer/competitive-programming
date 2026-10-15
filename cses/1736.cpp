#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1'000'000'007;

struct range_segtree {
    ll i, j, val, temp_a = 0, temp_d = 0;
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
        if (temp_a || temp_d) {
            ll len = j - i + 1;
            val += temp_a * len + temp_d * ((i + j) * len / 2);
            if (l) {
                l->temp_a += temp_a; l->temp_d += temp_d;
                r->temp_a += temp_a; r->temp_d += temp_d;
            }
            temp_a = temp_d = 0;
        }
    }
    void increase(int _i, int _j, ll a, ll d) {
        visit();
        if (_i <= i && j <= _j) {
            temp_a += a - d * _i;
            temp_d += d;
            visit();
        }
        else if (_j < i or j < _i) {
            // do nothing
        }
        else {
            l->increase(_i, _j, a, d);
            r->increase(_i, _j, a, d);
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
    vector<ll> t(n);
    for (ll i = 0; i < n; i++) cin >> t[i];
    range_segtree tree(t, 0, n - 1);
    for (ll i = 0; i < q; i++) {
        ll type, a, b;
        cin >> type >> a >> b;
        a--; b--;
        if (type == 1) tree.increase(a, b, 1, 1);
        else if (type == 2) cout << tree.query(a, b) << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}