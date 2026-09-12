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
    if (s[0] == '0') {
        cout << "0\n";
        return;
    }
    ll ans = 1;
    for (ll i = 0; i < s.size(); i++) {
        if (s[i] == '?') {
            if (i == 0) ans *= 9;
            else ans *= 10;
        }
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