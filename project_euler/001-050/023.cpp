#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

int sum_proper_divisors(int n) {
    int ans = 1;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            ans += i;
            if (n / i != i) ans += n / i;
        }
    }
    return ans;
}

bool is_abundant(ll n) {
    return sum_proper_divisors(n) > n;
}

void solve() {
    ll ans = 0;
    vector<ll> abundant;
    for (ll i = 1; i <= 28123; i++) {
        if (is_abundant(i)) abundant.push_back(i);
    }
    vector<bool> can_be_written(28124);
    for (ll i = 0; i < abundant.size(); i++) {
        for (ll j = 0; j < abundant.size(); j++) {
            if (abundant[i] + abundant[j] > 28123) continue;
            can_be_written[abundant[i] + abundant[j]] = true;
        }
    }
    for (ll i = 0; i <= 28123; i++) {
        if (!can_be_written[i]) ans += i;
    }
    cout << ans << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}