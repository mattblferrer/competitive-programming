#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1'000'000'007;

ll sum_interval(ll l, ll r) {
    ll lpref = ((l - 1) * l) / 2;
    ll rpref = (r * (r + 1)) / 2;
    return rpref - lpref;
}

void solve() {
    ll n, k;
    cin >> n >> k;
    ll left = k - 1, right = k + n, ans = 0;
    while (right - left > 1) {
        ll ai = (left + right) / 2;
        ans = sum_interval(k, ai) - sum_interval(ai + 1, k + n - 1);
        if (ans > 0) right = ai;
        else left = ai;
    }
    ll neg = abs(sum_interval(k, left) - sum_interval(left + 1, k + n - 1));
    ll pos = abs(sum_interval(k, right) - sum_interval(right + 1, k + n - 1));
    cout << min(neg, pos) << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    int t; cin >> t; while (t--) solve();
    return 0;
}