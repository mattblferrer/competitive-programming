#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

void solve() {
    ll n, q;
    cin >> n >> q;
    vector<ll> p(n + 1);
    map<ll, ll> mp;
    bool inv = false;

    for (ll i = 1; i <= n; i++) {
        cin >> p[i];
        mp[p[i]] = i;
    }
    for (ll i = 1; i <= q; i++) {
        ll type;
        cin >> type;
        if (type == 1) {
            ll x, y;
            cin >> x >> y;
            if (inv) {
                swap(mp[x], mp[y]);
                swap(p[mp[x]], p[mp[y]]);
            }
            else {
                swap(p[x], p[y]);
                swap(mp[p[x]], mp[p[y]]);
            }
        }
        else if (type == 2) {
            inv = 1 - inv;
        }
    }
    if (inv) {
        for (ll i = 1; i <= n; i++) cout << mp[i] << " ";
    }
    else {
        for (ll i = 1; i <= n; i++) cout << p[i] << " ";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}