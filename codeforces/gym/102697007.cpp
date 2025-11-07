#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

void solve() {
    ll h, m, s;
    string ampm;
    cin >> h >> m >> s >> ampm;
    ll ans = h * 3600 + m * 60 + s;
    if (ampm == "PM") ans += 3600 * 12;
    cout << ans;
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}