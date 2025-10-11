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
    string a, b;
    cin >> a >> b;
    for (ll i = 0; i < n; i++) {
        a[i] -= '0';
        b[i] -= '0';
    }
    for (ll i = 0; i < n; i++) {
        for (ll j = 0; j < n - 1; j++) {
            if ((a[j] == a[j + 1]) && (a[j + 1] == i % 2)) {
                a[j] = (i + 1) % 2;
                a[j + 1] = a[j];
            } 
            if ((b[j] == b[j + 1]) && (b[j + 1] == i % 2)) {
                b[j] = (i + 1) % 2;
                b[j + 1] = b[j];
            }
        }
    }
    for (ll i = 0; i < n; i++) {
        if (a[i] != b[i]) {
            cout << "NO\n";
            return;
        }
    }
    cout << "YES\n";
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    int t; cin >> t; while (t--) solve();
    return 0;
}