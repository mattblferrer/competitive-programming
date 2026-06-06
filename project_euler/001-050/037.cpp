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

bool is_truncatable(ll n) {
    string to_str = to_string(n);
    ll len = to_str.size();
    if (!is_prime(n)) return false;
    for (ll i = 1; i <= len; i++) {
        ll left = stoll(to_str.substr(0, i));
        ll right = stoll(to_str.substr(len - i, i));
        if (!is_prime(left)) return false;
        if (!is_prime(right)) return false;
    }
    return true;
}

void solve() {
    ll ans = 0, ctr = 0, curr = 10;
    while (ctr < 11) {
        if (is_truncatable(curr)) {
            ans += curr;
            ctr++;
        }
        curr++;
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