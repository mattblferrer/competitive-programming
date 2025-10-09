#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

void sieve(vector<bool>& is_prime, ll n) {
    is_prime.assign(n + 1, true);
    is_prime[0] = is_prime[1] = false;
    for (ll i = 2; i * i <= n; i++) {
        if (is_prime[i]) {
            for (ll j = i * i; j <= n; j += i) {
                is_prime[j] = false;
            }
        }
    }
}

void solve() {
    ll n, m;
    cin >> n >> m;
    vector<vector<ll>> a(n, vector<ll>(m));
    for (ll i = 0; i < n; i++) {
        for (ll j = 0; j < m; j++) cin >> a[i][j];
    }
    vector<bool> is_prime; 
    sieve(is_prime, 200000);
    vector<ll> primes(n);
    for (ll i = 0; i < 200000; i++) {
        if (is_prime[i]) primes.push_back(i);
    }
    ll ans = INF;
    for (ll i = 0; i < n; i++) {
        ll curr = 0;
        for (ll j = 0; j < m; j++) {
            curr += *lower_bound(primes.begin(), primes.end(), a[i][j]) - a[i][j];
        }
        ans = min(ans, curr);
    }
    for (ll j = 0; j < m; j++) {
        ll curr = 0;
        for (ll i = 0; i < n; i++) {
            curr += *lower_bound(primes.begin(), primes.end(), a[i][j]) - a[i][j];
        }
        ans = min(ans, curr);
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