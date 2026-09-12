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
    cin >> n;
    vector<ll> a(n);
    vector<ll> coins(3);
    for (ll i = 0; i < n; i++) cin >> a[i];
    for (ll i = 0; i < n; i++) {
        ll change = 1000 - (a[i] % 1000);
        if (change == 1000) change = 0;
        coins[2] += change / 100;
        change %= 100;
        coins[1] += change / 10;
        change %= 10;
        coins[0] += change;
    }
    for (ll i = 0; i < 3; i++) cout << coins[i] << " ";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}