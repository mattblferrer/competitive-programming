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
    ll ans = 0;
    vector<ll> mapping = {4, 1, 3, 2, 0, 5};
    for (ll i = 0; i < 6; i++) {
        ll bit = (n & (1 << i)) >> i;
        ans += bit * (1 << mapping[i]);
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