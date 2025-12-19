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
    if (n < 4) {
        cout << "NO\n";
        return;
    }
    cout << "YES\n";
    if (n % 2 == 0) {
        cout << "1 * 2 = 2\n";
        cout << "2 * 3 = 6\n";
        cout << "6 * 4 = 24\n";
        for (ll i = 5; i <= n; i += 2) {
            cout << i + 1 << " - " << i << " = 1\n";
            cout << "24 * 1 = 24\n";
        }
    }
    else {
        cout << "5 * 4 = 20\n";
        cout << "20 + 3 = 23\n";
        cout << "23 + 2 = 25\n";
        cout << "25 - 1 = 24\n";
        for (ll i = 6; i <= n; i += 2) {
            cout << i + 1 << " - " << i << " = 1\n";
            cout << "24 * 1 = 24\n";
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