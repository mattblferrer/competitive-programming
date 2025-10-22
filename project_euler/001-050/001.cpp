#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

void solve() {
    ll limit = 999;
    ll sum3 = 3 * (limit / 3) * (limit / 3 + 1);
    ll sum5 = 5 * (limit / 5) * (limit / 5 + 1);
    ll sum15 = 15 * (limit / 15) * (limit / 15 + 1);
    ll ans = (sum3 + sum5 - sum15) / 2;
    cout << ans;
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}