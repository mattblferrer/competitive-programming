#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1'000'000'007;

void solve() {
    ll n, v;
    cin >> n >> v;
    vector<ll> w(n);
    for (ll i = 0; i < n; i++) cin >> w[i];

    ll ans = 0;
    for (ll i = 0; i < n; i++) {
        for (ll j = i + 1; j < n; j++) {
            for (ll k = j + 1; k < n; k++) {
                if ((i + j + k + 3) > v) continue;
                ans = max(ans, w[i] + w[j] + w[k]);
            }
        }
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