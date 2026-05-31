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

bool is_pandigital(ll n) {
    string to_str = to_string(n);
    sort(to_str.begin(), to_str.end());
    for (int i = 0; i < to_str.size(); i++) {
        if (to_str[i] - '0' == 0) return false;
        if (to_str[i] - '0' > to_str.size()) return false;
    }
    for (int i = 0; i < to_str.size() - 1; i++) {
        if (to_str[i] == to_str[i + 1]) return false;
    }
    return true;
}

void solve() {
    int ans = 0;
    for (int i = 2; i < 10000000; i++) {
        if (is_prime(i) && is_pandigital(i)) ans = i;
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