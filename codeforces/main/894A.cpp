#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1'000'000'007;

void solve() {
    string s;
    cin >> s;
    ll ans = 0;
    ll n = s.size();
    for (ll i = 0; i < n; i++) {
        for (ll j = i + 1; j < n; j++) {
            for (ll k = j + 1; k < n; k++) {
                if ((s[i] == 'Q') && (s[j] == 'A') && (s[k] == 'Q')) ans++;
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