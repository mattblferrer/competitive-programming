#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

void solve() {
    ll a, b;
    cin >> a >> b;
    for (ll i = a; i <= b; i++) {
        for (ll j = 2; j*j <= i; j++) { 
            if (i % j == 0) {
                cout << j << " " << i - j << "\n";
                return;
            }
        }
    }
    cout << "-1\n";
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    int t; cin >> t; while (t--) solve();
    return 0;
}