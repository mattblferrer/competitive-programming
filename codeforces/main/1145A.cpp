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
    ll ans = 0;
    for (ll p = 1; p <= n; p *= 2) {
        for (ll i = 0; i < n; i += p) {
            bool sorted = true;
            for (ll j = i; j < i + p - 1; j++) {
                if (a[j] > a[j + 1]) sorted = false;
            }
            if (sorted) ans = max(ans, p);
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