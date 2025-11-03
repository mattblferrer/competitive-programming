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
    ll ans = 0;
    while (true) {
        ans = 0;
        while (n > 0) {
            ans += n % 10;
            n /= 10;
        }
        if (ans < 10) {
            cout << ans;
            return;
        }
        n = ans;
    }
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}