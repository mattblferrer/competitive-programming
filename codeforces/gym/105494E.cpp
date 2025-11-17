#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

ll calc_ranges(vector<ll>& a, ll k) {
    ll n = a.size();
    ll m = 1;
    for (ll i = 0; i < n - 1; i++) {
        if (abs(a[i + 1] - a[i]) > k) m++;
    }
    return m;
}

void solve() {
    ll n, m;
    cin >> n >> m;
    vector<ll> a(n);
    for (ll i = 0; i < n; i++) cin >> a[i];

    ll left = 0, right = pow(10, 6);
    while (right - left > 1) {
        ll mid = (left + right) / 2;
        if (calc_ranges(a, mid) <= m) right = mid; 
        else left = mid; 
    }
    ll r = calc_ranges(a, right);
    if (r != m) cout << -1;
    else cout << right;
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}