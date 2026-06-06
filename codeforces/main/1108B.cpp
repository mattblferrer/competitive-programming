#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

void solve() {
    ll n;
    cin >> n;
    vector<ll> d(n);
    for (ll i = 0; i < n; i++) cin >> d[i];
    sort(d.begin(), d.end());

    ll g = 1, x = d.back(), y = 1;
    for (ll i = 0; i < n - 1; i++) {
        if (d[i] == d[i + 1]) {
            g = lcm(g, d[i]);
            i++;
        }
        else if (x % d[i] != 0) y = lcm(y, d[i]);
    }
    y = lcm(y, g);

    cout << x << " " << y << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}