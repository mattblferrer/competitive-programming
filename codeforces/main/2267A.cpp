#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1'000'000'007;

void solve() {
    ll n;
    char c;
    cin >> n >> c;
    string s;
    cin >> s;

    ll ans = 0;
    for (ll i = 0; i < n / 2; i++) {
        if (s[i] == s[n - i - 1]) continue;
        if (s[i] != c) ans++;
        if (s[n - i - 1] != c) ans++;
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