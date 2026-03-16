#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

void solve() {
    ll n;
    cin >> n;
    vector<ll> a(n);
    for (ll i = 0; i < n; i++) cin >> a[i];
    ll ans = 0, left = 0, right = 0;
    for (ll i = 0; i < n; i++) {
        if (a[i] <= 500000) left = max(left, a[i] - 1);
        else right = max(right, 1000000 - a[i]);
    }
    ans = max(left, right);
    cout << ans;
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}