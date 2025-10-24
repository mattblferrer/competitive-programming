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
    vector<ll> a(n);
    for (ll i = 0; i < n; i++) cin >> a[i];
    ll ans = 0;
    bool valid = false;
    for (ll i = 0; i < n - k; i++) {
        if (valid) {
            if (a[i + k - 1] / 2 < a[i + k]) ans++;
            else valid = false;
            continue; 
        }
        valid = true;
        for (ll j = i; j < i + k; j++) {
            if (a[j] / 2 >= a[j + 1]) {
                valid = false; 
                i = j;
                break;
            }
        }
        if (valid) ans++;
    }
    cout << ans << "\n";
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    int t; cin >> t; while (t--) solve();
    return 0;
}