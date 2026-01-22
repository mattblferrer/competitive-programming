#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

void solve() {
    ll r1, c1, r2, c2;
    cin >> r1 >> c1 >> r2 >> c2;
    ll r = 0, b = 0, k = 0;
    if (r1 != r2) r++;
    if (c1 != c2) r++;
    if (r1 + c1 == r2 + c2) b = 1;
    else if (r1 - c1 == r2 - c2) b = 1;
    else if ((r1 + c1) % 2 == (r2 + c2) % 2) b = 2;
    k = max(abs(r2 - r1), abs(c2 - c1));
    cout << r << " " << b << " " << k;
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}