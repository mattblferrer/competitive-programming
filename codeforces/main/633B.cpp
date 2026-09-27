#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1'000'000'007;

void solve() {
    ll m;
    cin >> m;
    ll fac = 0;
    vector<ll> ans;
    for (ll i = 1; i <= INF; i++) {
        ll check = i;
        while (check % 5 == 0) {
            fac++;
            check /= 5;
        }
        if (fac == m) ans.push_back(i);
        else if (fac > m) break;
    }
    cout << ans.size() << "\n";
    for (ll k : ans) cout << k << " ";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}