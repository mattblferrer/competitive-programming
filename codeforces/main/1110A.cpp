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

void solve() {
    ll b, k;
    cin >> b >> k;
    vector<ll> a(k);
    for (ll i = 0; i < k; i++) cin >> a[i];
    ll par = 0;
    for (ll i = 0; i < k; i++) {
        par = (par + a[i]*binexp(b, k - i - 1, 2)) % 2;
    }
    if (par == 0) cout << "even";
    else cout << "odd";
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}