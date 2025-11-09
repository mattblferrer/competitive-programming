#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

void solve() {
    ll c, k;
    cin >> c >> k;
    string s;
    cin >> s;
    ll curr = 0, ans = 0;
    for (ll i = 0; i < c; i++) {
        if (s[i] == '0') curr++;
        else curr = 0;
        ans = max(ans, curr);
    }
    if (ans > k) cout << "yes\n";
    else cout << "no\n";
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    int t; cin >> t; while (t--) solve();
    return 0;
}