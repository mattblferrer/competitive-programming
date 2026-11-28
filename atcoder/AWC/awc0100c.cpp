#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1'000'000'007;

void solve() {
    ll n, l, q;
    cin >> n >> l >> q;
    vector<string> s(n);
    for (ll i = 0; i < n; i++) cin >> s[i];

    vector<vector<ll>> c(q);
    for (ll i = 0; i < q; i++) {
        ll mi;
        cin >> mi;
        for (ll j = 0; j < mi; j++) {
            ll cij;
            cin >> cij;
            cij--;
            c[i].push_back(cij);
        }
    }
    for (ll i = 0; i < q; i++) {
        string curr = "";
        for (ll j = 0; j < l; j++) curr += '0';
        for (ll j = 0; j < c[i].size(); j++) {
            for (ll k = 0; k < l; k++) {
                if (s[c[i][j]][k] == '1') curr[k] = '1';
            }
        }
        cout << curr << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}