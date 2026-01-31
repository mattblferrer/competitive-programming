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
    vector<ll> p(n), np(n);
    for (ll i = 0; i < n; i++) cin >> p[i];
    vector<bool> taken(n);
    if (n == 1) {
        cout << "-1\n";
        return;
    }
    for (ll i = 0; i < n; i++) {
        for (ll j = 0; j < n; j++) {
            if ((taken[j]) || (p[i] == j + 1)) continue;
            np[i] = j + 1;
            taken[j] = true;
            break;
        }
        if (np[i] == 0) np[i] = p[i];
    }
    if (np[n - 1] == p[n - 1]) {
        ll temp = np[n - 1];
        np[n - 1] = np[n - 2];
        np[n - 2] = temp;
    }
    for (ll i = 0; i < n; i++) cout << np[i] << " ";
    cout << "\n";
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    int t; cin >> t; while (t--) solve();
    return 0;
}