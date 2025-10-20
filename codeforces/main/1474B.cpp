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
    ll d;
    cin >> d;
    vector<bool> is_prime;
    sieve(is_prime, 40000);
    vector<ll> primes;
    for (int i = 0; i < 40000; i++) {
        if (is_prime[i]) primes.push_back(i);
    }
    ll a = *lower_bound(primes.begin(), primes.end(), d + 1);
    ll b = *lower_bound(primes.begin(), primes.end(), a + d);
    cout << a * b << "\n";
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    int t; cin >> t; while (t--) solve();
    return 0;
}