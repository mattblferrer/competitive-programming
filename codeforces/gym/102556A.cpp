#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

void solve() {
    string s;
    cin >> s;
    ll n = s.size();
    ll total = 0;
    for (ll i = 0; i < n; i++) {
        if (s[i] == '.') total++;
    }
    s += s;
    ll ans = 0, curr = 0;
    for (ll i = 0; i < 2*n; i++) {
        if (s[i] == '.') curr++;
        else curr = 0;
        ans = max(ans, curr);
        if (ans >= n) ans = n;
    }
    ans = total - ans;
    cout << ans;
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}