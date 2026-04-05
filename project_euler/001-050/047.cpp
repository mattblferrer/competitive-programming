#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

set<ll> prime_factors(ll n) {
    set<ll> factors;
    for (ll i = 2; i*i <= n; i++) {
        if (n % i == 0) factors.insert(i);
        while (n % i == 0) n /= i;
    }
    if (n != 1) factors.insert(n);
    return factors;
}

void solve() {
    ll n = 2;
    deque<ll> curr;
    while (true) {
        curr.push_back(prime_factors(n).size());
        if (curr.size() > 4) curr.pop_front();
        bool ok = true;
        for (ll i = 0; i < 4; i++) {
            if (curr[i] != 4) ok = false;
        }
        if (ok) {
            cout << n - 3;
            return;
        }
        n++;
    }
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}