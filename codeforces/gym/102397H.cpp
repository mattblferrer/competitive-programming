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
    ll n;
    cin >> n;
    map<ll, ll> cnt;
    for (ll i = 0; i < n; i++) {
        ll ai;
        cin >> ai;
        cnt[ai]++;
    }
    ll ans = 0;
    for (const auto& pair: cnt) {
        ans = (ans + binexp(2, pair.second, MOD) - 1) % MOD;
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