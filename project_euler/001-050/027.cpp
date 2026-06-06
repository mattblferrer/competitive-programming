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

void solve() {
    ll max_p = 0, max_a = 0, max_b = 0;
    for (ll a = -1000; a <= 1000; a++) {
        for (ll b = -1000; b <= 1000; b++) {
            for (ll n = 0; n <= b; n++) {
                ll curr = n * n + a * n + b;
                if (!is_prime(curr)) {
                    if (max_p < n) {
                        max_p = n;
                        max_a = a;
                        max_b = b;
                    }
                    break;
                }
            }
        }
    }
    cout << max_a * max_b;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}