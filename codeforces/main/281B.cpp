#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

void solve() {
    ll x, y, n;
    cin >> x >> y >> n;
    ld min_diff = INF, num = 0, den = 0;
    for (ll i = 1; i <= n; i++) {
        ld diff = (ld)min((x * i) % y, y - (x * i) % y) / (i * y);
        if (min_diff > diff) {
            if ((x * i) % y > y - (x * i) % y) num = (x * i) / y + 1;
            else num = (x * i) / y;
            den = i;
            min_diff = diff;
        }
    }
    cout << num << "/" << den;
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}