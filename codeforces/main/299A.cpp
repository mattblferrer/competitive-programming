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
    ll g = a[0];
    for (ll i = 1; i < n; i++) {
        g = gcd(g, a[i]);
    }
    for (ll i = 0; i < n; i++) {
        if (g % a[i] == 0) {
            cout << a[i];
            return;
        }
    }
    cout << -1;
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}