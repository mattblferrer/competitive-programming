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
    vector<ll> a(n);
    for (ll i = 0; i < n; i++) cin >> a[i];
    bool all_evens = true;
    for (ll i = 0; i < n; i++) {
        if (a[i] % 2 == 1) {
            all_evens = false;
            break;
        }
    }
    if (all_evens) {
        cout << "-1\n";
        return;
    }
    ll evens = 0;
    for (ll i = 0; i < n; i++) {
        if (a[i] % 2 == 0) evens++;
    }
    cout << evens << "\n";
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    int t; cin >> t; while (t--) solve();
    return 0;
}