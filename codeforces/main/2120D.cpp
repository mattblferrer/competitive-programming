#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

ll binexp(ll a, ll b, ll mod) {
    ll ans = 1;
    while (b) {
        if (b % 2) {
            ans = (ans * a) % mod;
        }
        a = (a * a) % mod;  
        b >>= 1;
    }
    return ans;
}

ll modinv_p(ll a, ll p) {
    return binexp(a, p - 2, p);
}

ll comb_m(ll n, ll k, ll mod) {
    if (k < 0) return 0;
    if (k == 0) return 1;
    ll num = 1, denom = 1;
    for (ll i = n; i >= n - k + 1; i--) num = (num * i) % mod;
    for (ll i = 1; i <= k; i++) denom = (denom * i) % mod;
    return (num * modinv_p(denom, mod)) % mod;
}

void solve() {
    ll a, b, k;
    cin >> a >> b >> k;
    ll n = (k * (a - 1) + 1) % MOD; 
    ll m = (((k * (b - 1)) % MOD) * comb_m(n, a, MOD) + 1) % MOD;
    cout << n << " " << m << "\n";
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    int t; cin >> t; while (t--) solve();
    return 0;
}