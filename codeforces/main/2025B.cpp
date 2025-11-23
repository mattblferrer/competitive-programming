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
    ll t;
    cin >> t;
    vector<ll> n(t), k(t);
    for (ll i = 0; i < t; i++) cin >> n[i];
    for (ll i = 0; i < t; i++) cin >> k[i];
    for (ll i = 0; i < t; i++) {
        cout << binexp(2, k[i], MOD) << "\n";
    }
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}