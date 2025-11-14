#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

void solve() {
    ll n;
    cin >> n;
    vector<ll> x(n), y(n);
    for (ll i = 0; i < n; i++) cin >> x[i];
    for (ll i = 0; i < n; i++) cin >> y[i];
    ll ans = 0;
    for (ll i = 0; i < n; i++) {
        for (ll j = i + 1; j < n; j++) {
            ans = max(ans, abs(x[i]-x[j])*abs(x[i]-x[j]) + abs(y[i]-y[j])*abs(y[i]-y[j]));
        }
    }
    cout << ans;
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}