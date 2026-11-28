#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

void solve() {
    ll m, d;
    string s;
    cin >> m >> d >> s;
    vector<bool> watched(m);
    for (ll i = 0; i < m; i++) {
        if (s[i] == 'G') {
            for (ll j = i - d; j <= i + d; j++) {
                if ((j < 0) || (j >= m)) continue;
                watched[j] = true;
            }
        }
    }
    ll ans = 0;
    for (ll i = 0; i < m; i++) {
        if (!watched[i]) ans++;
    }
    cout << ans << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}