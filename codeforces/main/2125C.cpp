#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

ll upto = 0;

void precompute() {
    for (ll i = 0; i <= 210; i++) {
        bool valid = true;
        for (ll j: {2, 3, 5, 7}) {
            if (i % j == 0) valid = false;
        }
        if (valid) upto++;
    }
}

ll good_numbers(ll n) {
    ll ans = upto*(n / 210);
    for (ll i = n - n % 210; i <= n; i++) {
        bool valid = true;
        for (ll j: {2, 3, 5, 7}) {
            if (i % j == 0) valid = false;
        }
        if (valid) ans++;
    }
    return ans;
}

void solve() {
    ll l, r;
    cin >> l >> r;
    cout << good_numbers(r) - good_numbers(l - 1) << "\n";
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    precompute();
    int t; cin >> t; while (t--) solve();
    return 0;
}