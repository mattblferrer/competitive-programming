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

void solve() {
    ll n;
    cin >> n;
    vector<ll> a(n);
    for (ll i = 0; i < n; i++) cin >> a[i];
    ll sum = 0;
    for (ll i = 0; i < n; i++) sum += a[i];
    ll p = 0, q = (n*(n - 1)/2) % MOD;
    for (ll i = 0; i < n; i++) {
        p = (p + ((sum - a[i]) % MOD)*a[i]) % MOD;
    }
    p = (p * modinv_p(2, MOD)) % MOD;
    cout << (p * modinv_p(q, MOD)) % MOD << "\n";
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    int t; cin >> t; while (t--) solve();
    return 0;
}