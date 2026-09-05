#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1'000'000'007;

void solve() {
    ll n, k;
    cin >> n >> k;
    string s;
    cin >> s;

    ll ans = 0;
    for (ll i = 0; i < n / k; i++) {
        ll sum = 0;
        for (ll j = k * i; j < k * i + k; j++) {
            sum += (s[j] == '1') ? 1 : 0;
        }
        if (sum == k) ans++;
    }
    cout << ans << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    int t; cin >> t; while (t--) solve();
    return 0;
}