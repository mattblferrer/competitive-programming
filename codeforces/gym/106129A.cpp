#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

void solve() {
    ll l, r;
    cin >> l >> r;
    ll n = l + r;
    if (r == l - 1) cout << n;
    else if ((r == l) || (r == l - 2)) cout << n + n/2;
    else cout << 2*n;
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}