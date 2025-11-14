#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

void solve() {
    ll x;
    cin >> x;
    for (ll i = 3; i <= x; i++) {
        ll c = x;
        while (c % i == 0) c /= i;
        if (c != 1) continue;
        cout << i - 1;
        return;
    }
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}