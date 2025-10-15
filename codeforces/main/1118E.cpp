#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

void solve() {
    ll n, k;
    cin >> n >> k;
    if (n > k * (k - 1)) {
        cout << "NO\n";
        return;
    }
    cout << "YES\n";
    for (ll i = 1; i <= k; i++) {
        for (ll j = i + 1; j <= k; j++) {
            if (n > 0) {
                cout << i << " " << j << "\n";
                n--;
            }
            else break;
            if (n > 0) {
                cout << j << " " << i << "\n";
                n--;
            }
            else break;
        }
    }
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}