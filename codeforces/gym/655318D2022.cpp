#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

ll style(ll n) {
    ll ans = 1;
    while (n > 0) {
        ans *= n % 10;
        n /= 10;
    }
    return ans;
}

void solve() {
    ll l, r;
    cin >> l >> r;
    ll prod = INF;
    for (ll i = l; i <= r; i++) {
        prod = min(prod, style(i));
        if (prod == 0) {
            cout << prod;
            return;
        }
    }
    cout << prod;
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}