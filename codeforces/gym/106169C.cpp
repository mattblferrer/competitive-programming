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
    ll n;
    cin >> n;
    set<ll> nums;
    for (ll i = 2; powl(3, i) <= n; i += 2) {
        if (!is_prime(i + 1)) continue;
        for (ll j = 3; powl(j, i) <= n; j += 2) {
            if (!is_prime(j)) continue;
            nums.insert(powl(j, i));
        }
    }
    cout << nums.size();
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}