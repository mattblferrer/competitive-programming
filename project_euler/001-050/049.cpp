#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

vector<ll> primes;

bool is_prime(ll n) {
    if (n == 2) return true;
    if (n % 2 == 0) return false;
    for (ll i = 3; i * i <= n; i += 2) {
        if (n % i == 0) return false;
    }
    return n > 1;
}

bool is_permutation(ll a, ll b, ll c) {
    string as = to_string(a), bs = to_string(b), cs = to_string(c);
    sort(as.begin(), as.end());
    sort(bs.begin(), bs.end());
    sort(cs.begin(), cs.end());
    return (as == bs) && (bs == cs);
}

void solve() {
    for (ll i = 1000; i <= 10000; i++) {
        if (is_prime(i)) primes.push_back(i);
    }
    for (ll i = 0; i < primes.size(); i++) {
        for (ll j = i + 1; j < primes.size(); j++) {
            ll pi = primes[i], pj = primes[j];
            ll diff = pj - pi;
            ll pk = pj + diff;
            if (pi == 1487 && pj == 4817 && pk == 8147) continue;
            if (!is_permutation(pi, pj, pk)) continue;
            if (!is_prime(pk)) continue;

            cout << pi << pj << pk;
            return;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}