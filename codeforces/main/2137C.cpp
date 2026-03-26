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
    if ((a % 2 == 0) && (b % 2 == 0)) {
        cout << a*b/2 + 2 << "\n";
        return;
    }
    if ((a % 2 == 0) && (b % 2 == 1)) {
        cout << "-1\n";
        return;
    }
    if ((a % 2 == 1) && (b % 2 == 0)) {
        if (b % 4 == 0) cout << 2 + a*b/2 << "\n";
        else cout << "-1\n";
        return;
    }
    if ((a % 2 == 1) && (b % 2 == 1)) {
        cout << a*b + 1 << "\n";
        return;
    }
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    int t; cin >> t; while (t--) solve();
    return 0;
}