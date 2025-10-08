#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

void solve() {
    ll n, k, x, a, b, c;
    cin >> n >> k >> x >> a >> b >> c;
    ll ans = 0, sum = x, x_prev = x;
    for (ll i = 2; i <= k; i++) {
        x = (a * x + b) % c;
        sum ^= x;
    }
    for (ll i = k; i <= n; i++) {
        ans ^= sum;
        sum ^= x_prev;
        x_prev = (a * x_prev + b) % c;
        x = (a * x + b) % c;
        sum ^= x;
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