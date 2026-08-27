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
    for (ll i = 0; i < s.size(); i++) {
        ll last1 = s[i] - '0';
        if (last1 % 4 == 0) ans++;
    }
    for (ll i = 1; i < s.size(); i++) {
        ll last2 = 10 * (s[i - 1] - '0') + (s[i] - '0');
        if (last2 % 4 == 0) ans += i;
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