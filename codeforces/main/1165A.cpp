#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

void solve() {
    ll n, x, y;
    cin >> n >> x >> y;
    string s;
    cin >> s;
    ll ans = 0;
    for (ll i = n - x; i < n; i++) {
        if (i == n - y - 1 && s[i] == '0') {
            ans++;
        }
        if (i != n - y - 1 && s[i] == '1') {
            ans++;
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