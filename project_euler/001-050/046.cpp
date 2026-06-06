#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

bool is_prime(ll n) {
    if (n == 2) return true;
    if (n % 2 == 0) return false;
    for (ll i = 3; i * i <= n; i += 2) {
        if (n % i == 0) return false;
    }
    return n > 1;
}

bool expressed(ll n) {
    for (ll i = 1; 2 * i * i <= n; i++) {
        if (is_prime(n - 2 * i * i)) return true;
    }
    return false;
}

void solve() {
    ll curr = 9;
    while (true) {
        if (is_prime(curr)) {
            curr += 2;
            continue;
        }
        if (!expressed(curr)) {
            cout << curr;
            return;
        }
        curr += 2;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}