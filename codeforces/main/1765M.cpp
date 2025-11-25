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
    for (ll i = 2; i*i <= n; i++) {
        if (n % i == 0) {
            cout << n / i << " " << (i - 1)*n / i << "\n";
            return;
        }
    }
    cout << 1 << " " << n - 1 << "\n";
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    int t; cin >> t; while (t--) solve();
    return 0;
}