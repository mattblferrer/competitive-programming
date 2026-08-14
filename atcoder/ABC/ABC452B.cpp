#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

void solve() {
    ll h, w;
    cin >> h >> w;
    for (ll j = 0; j < w; j++) cout << "#";
    cout << "\n";
    for (ll i = 1; i < h - 1; i++) {
        cout << "#";
        for (ll j = 1; j < w - 1; j++) {
            cout << ".";
        }
        cout << "#\n";
    }
    for (ll j = 0; j < w; j++) cout << "#";
    cout << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}