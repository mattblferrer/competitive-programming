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
    sort(a.begin(), a.end());
    ll g = a[0];
    for (ll i = 0; i < n - 1; i++) {
        g = gcd(g, gcd(a[i], a[i + 1]));
        if (g == 1) break;
    }
    ll ans = 0;
    for (ll i = 1; i * i <= g; i++) {
        if (g % i == 0) {
            ans++;
            if (i != g / i) ans++; 
        }
    }
    cout << ans << "\n";
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}