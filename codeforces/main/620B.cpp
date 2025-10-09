#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

void solve() {
    ll a, b;
    cin >> a >> b;
    vector<ll> seg = {6, 2, 5, 5, 4, 5, 6, 3, 7, 6};
    ll ans = 0;
    for (ll i = a; i <= b; i++) {
        ll curr = i;
        while (curr > 0) {
            ans += seg[curr % 10];
            curr /= 10;
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