#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

void solve() {
    ll n, d, v;
    cin >> n >> d >> v;
    vector<ll> s(n);
    for (ll i = 0; i < n; i++) cin >> s[i];
    ll ans = 0;
    for (ll i = 0; i < n; i++) {
        if (s[i] > v) ans++;
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