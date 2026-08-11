#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 1e18;
const ll MOD = 1000000007;

void solve() {
    ll n, c;
    cin >> n >> c;
    vector<ll> a(n);
    for (ll i = 0; i < n; i++) cin >> a[i];

    ll left = 0, right = INF;
    while (right - left > 1) {
        ll w = (left + right) / 2;
        ll area = 0;
        bool overflow = false;
        for (ll i = 0; i < n; i++) {
            ll curr = 0;
            if (__builtin_mul_overflow(a[i] + 2*w, a[i] + 2*w, &curr)) {
                right = w;
                overflow = true;
                break;
            }
            if (__builtin_add_overflow(area, curr, &area)) {
                right = w;
                overflow = true;
                break;
            }
        }
        if (overflow) continue;
        if (area <= c) left = w;
        else right = w;
    }
    cout << left << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    int t; cin >> t; while (t--) solve();
    return 0;
}