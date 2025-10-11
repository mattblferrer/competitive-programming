#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

void solve() {
    ll g, w, r, t;
    cin >> g >> w >> r >> t;
    t = t % (g + w + r);
    if (t < g) cout << "Guiding Beat\n";
    else if (t < (g + w)) cout << "Warning Beat\n";
    else cout << "Resting Phase\n";
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    int t; cin >> t; while (t--) solve();
    return 0;
}