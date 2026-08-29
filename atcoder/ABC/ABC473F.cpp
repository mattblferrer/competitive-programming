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
            val = min(l->val, r->val);
        }
    }
    void visit() {
        if (temp_val) {
            val += temp_val;
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
            val = min(l->val, r->val);
        }
    }
    ll query(int _i, int _j) {
        visit();
        if (_i <= i and j <= _j) return val;
        else if (_j < i || j < _i) return INF;
        else return min(l->query(_i, _j), r->query(_i, _j));
    }
};

void solve() {
    ll n, q;
    string s;
    cin >> n >> s >> q;

    vector<ll> pref(n + 1);
    for (ll i = 1; i <= n; i++) {
        pref[i] = pref[i - 1] + ((s[i - 1] == 'A') ? 1 : -1);
    }
    range_segtree tree(pref, 0, n + 1);

    for (ll qc = 0; qc < q; qc++) {
        ll type;
        cin >> type;
        if (type == 1) {
            ll i;
            char c;
            cin >> i >> c;
            if (s[i - 1] == c) continue;
            if (c == 'A') {
                tree.increase(i, n, 2);
            }
            else if (c == 'B') {
                tree.increase(i, n, -2);
            }
            s[i - 1] = c;
        }

        else if (type == 2) {
            ll l, r;
            cin >> l >> r;

            ll left = tree.query(l - 1, l - 1), right = tree.query(r, r), range = tree.query(l - 1, r);
            if (range < left) {
                cout << "No\n";
            }
            else cout << "Yes\n";
        }

        else cerr << "invalid type";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}