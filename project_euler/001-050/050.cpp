#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

vector<bool> is_prime;

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
    ll limit = 1000000;
    sieve(is_prime, limit);
    vector<ll> primes;
    ll ans = 0, max_len = 0;
    for (ll i = 0; i < limit; i++) {
        if (is_prime[i]) primes.push_back(i);
    }

    for (ll i = 0; i < primes.size() - 1; i++) {
        ll curr = primes[i], len = 1;
        while (curr + primes[i + len] < limit) {
            curr += primes[i + len];
            len++;
            if (is_prime[curr] && max_len < len) {
                max_len = len;
                ans = curr;
            }
            if (i + len >= primes.size()) break;
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