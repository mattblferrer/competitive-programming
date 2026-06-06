#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

bool satisfied(ll n) {
    ll sum_5 = 0;
    string to_str = to_string(n);
    for (ll i = 0; i < to_str.size(); i++) {
        sum_5 += pow(to_str[i] - '0', 5);
    }
    return n == sum_5;
}

void solve() {
    ll ans = 0;
    for (ll i = 10; i < 1000000; i++) {
        if (satisfied(i)) ans += i;
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