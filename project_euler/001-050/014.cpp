#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

ll chain_length(ll n) {
    ll steps = 0;
    while (n > 1) {
        if (n % 2 == 0) n /= 2;
        else n = 3*n + 1;
        steps++;
    }
    return steps;
}

void solve() {
    ll max_l = 0, ans = 0;
    for (ll i = 1; i <= 1000000; i++) {
        ll chain = chain_length(i);
        if (max_l < chain) {
            max_l = chain;
            ans = i;
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