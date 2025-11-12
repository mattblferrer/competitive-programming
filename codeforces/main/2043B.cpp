#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

void solve() {
    ll n, d;
    cin >> n >> d;
    cout << "1 ";
    if ((n >= 3) || (d == 3) || (d == 6) || (d == 9)) cout << "3 ";
    if (d == 5) cout << "5 ";
    if ((n >= 3) || (d == 7)) cout << "7 ";
    if ((n >= 6) || ((d == 3) && (n >= 3)) || 
        ((d == 6) && (n >= 3)) || (d == 9)) cout << "9 ";
    cout << "\n";
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    int t; cin >> t; while (t--) solve();
    return 0;
}