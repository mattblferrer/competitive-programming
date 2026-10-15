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
    ll n;
    cin >> n;
    string s;
    cin >> s;
    vector<ll> arrs(n);
    for (ll i = 0; i < n; i++) {
        arrs[i] = (i + 1) * (n - i);
    }

    map<ll, vector<ll>> pos;
    pos[2].push_back(-1);
    for (ll i = 0; i < n; i++) {
        pos[s[i] - '0'].push_back(i);
    }
    pos[0].push_back(n);
    pos[2].push_back(n);
    pos[5].push_back(n);
    pos[6].push_back(n);

    range_segtree tree(arrs, 0, n - 1);
    for (ll i = 0; i < n; i++) {
        ll pos2l = *lower_bound(pos[2].begin(), pos[2].end(), i);
        ll pos0 = *lower_bound(pos[0].begin(), pos[0].end(), pos2l);
        ll pos2r = *lower_bound(pos[2].begin(), pos[2].end(), pos0);
        if ((pos2l == -1) || (pos2r == n)) continue;

        ll pos5 = *lower_bound(pos[5].begin(), pos[5].end(), pos2r);
        ll pos6 = *lower_bound(pos[6].begin(), pos[6].end(), pos2r);
        if (pos6 <= pos5) continue;

        tree.increase(i, pos5, -(pos6 - pos5), 0);
        tree.increase(pos5 + 1, pos6, -(pos6 - pos5 - 1), 1);
    }

    vector<ll> ans(n);
    for (ll i = 0; i < n; i++) ans[i] = tree.query(i, i);
    for (ll i = 0; i < n; i++) cout << ans[i] << " ";
    cout << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    int t; cin >> t; while (t--) solve();
    return 0;
}