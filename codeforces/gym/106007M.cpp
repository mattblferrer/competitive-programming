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
    if (n == 1) { cout << "1\n"; return; }
    if (n == 2) { cout << "1 2\n"; return; }

    for (ll p = 1; p <= n; p *= 2) {
        if (p == n) {
            cout << 1 << " " << n << " ";
            for (ll i = 2; i < n; i++) cout << i << " ";
            cout << "\n";
            return;
        }
        if (p == n - 1) {
            cout << 1 << " " << n << " " << n - 1 << " ";
            for (ll i = 2; i < n - 1; i++) cout << i << " ";
            cout << "\n";
            return;
        }
    }

    cout << n << " ";
    ll small_bit = 0;
    for (ll p = 1; p <= n; p *= 2) {
        if (n & p) {
            small_bit = p;
            break;
        }
    }
    for (ll p = 1; p <= n; p *= 2) {
        if (n & p) {
            for (ll i = n - p; i < n; i++) {
                if ((i == small_bit) || (i == 0)) continue;
                cout << i << " ";
            }
            n -= p;
        }
    }
    cout << small_bit << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    int t; cin >> t; while (t--) solve();
    return 0;
}