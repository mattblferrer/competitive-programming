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
    ll n = s.size();
    set<ll> possible = {0};
    for (ll i = 1; i < n - 1; i++) {
        if ((s[i - 1] == s[i]) && (s[i] == s[i + 1])) possible.insert(1);
        if ((s[i - 1] != s[i]) && (s[i] != s[i + 1])) possible.insert(-1);
    }
    ll ans = possible.size();
    cout << ans << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    int t; cin >> t; while (t--) solve();
    return 0;
}