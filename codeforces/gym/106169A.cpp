#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

void solve() {
    vector<ll> v(7);
    for (ll i = 1; i <= 6; i++) cin >> v[i];
    ll ans = v[1]*v[3]*v[5] + v[1]*v[3]*v[6] + v[1]*v[4]*v[5] + v[1]*v[4]*v[6]
        + v[2]*v[3]*v[5] + v[2]*v[3]*v[6] + v[2]*v[4]*v[5] + v[2]*v[4]*v[6];
    cout << ans;
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}