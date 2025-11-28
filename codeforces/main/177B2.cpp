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
    ll ans = n;
    while (n > 1) {
        bool found = false;
        for (ll i = 2; i*i <= n; i++) {
            if (n % i == 0) {
                ans += n / i;
                n /= i;
                found = true;
                break;
            }
        }
        if (!found) {
            ans ++;
            break;
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