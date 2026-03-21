#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 10000000000;

void solve() {
    ll ans = 0;
    for (ll i = 1; i <= 1000; i++) {
        ll curr = 1;
        for (ll j = 1; j <= i; j++) {
            curr = (curr * i) % MOD;
        }
        ans = (ans + curr) % MOD;
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