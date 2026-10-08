#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1'000'000'007;

void solve() {
    ll n, q;
    cin >> n >> q;
    vector<pll> queries(q);
    set<ll> no_tiles;
    vector<bool> colored(n);
    for (ll i = 0; i < n; i++) no_tiles.insert(i);

    for (ll i = 0; i < q; i++) {
        ll type;
        cin >> type;
        if (type == 1) {
            ll x;
            cin >> x;
            x--;
            queries[i] = {type, x};
            if (no_tiles.count(x)) no_tiles.erase(x);
            else no_tiles.insert(x);
        }
        else if (type == 2) {
            char c;
            cin >> c;
            queries[i] = {type, c};
        }
    }
    vector<char> ans(n);
    for (ll i = q - 1; i >= 0; i--) {
        ll type = queries[i].first;
        if (type == 1) {
            ll x = queries[i].second;
            if (no_tiles.count(x)) no_tiles.erase(x);
            else if (!colored[x]) no_tiles.insert(x);
        }
        else {
            char c = queries[i].second;
            vector<ll> to_erase;
            for (ll x : no_tiles) {
                ans[x] = c;
                colored[x] = true;
                if (no_tiles.count(x)) to_erase.push_back(x);
            }
            for (ll x : to_erase) no_tiles.erase(x);
        }
    }
    for (ll i = 0; i < n; i++) {
        if (!colored[i]) ans[i] = 'a';
    }
    for (ll i = 0; i < n; i++) cout << ans[i];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}