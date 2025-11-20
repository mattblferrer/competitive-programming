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
    if (a >= b) {
        if (b == 0) cout << 2*a + 1;
        else cout << 0;
    }
    else {
        if (2*a > b) cout << 0;
        else cout << b + 1;
    }
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}