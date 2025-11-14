#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

void solve() {
    vector<ll> a(4);
    vector<bool> seen(4);
    for (ll i = 0; i < 4; i++) cin >> a[i];
    for (ll i = 1; i < 4; i++) {
        if (a[i] + a[0] == 100) {
            cout << "Train 1 and Train " << (i + 1) << "\n";
            seen[0] = true;
            seen[i] = true;
        }
    }
    for (ll i = 0; i < 4; i++) {
        if (!seen[i]) {
            cout << "Train " << (i + 1) << " and Train ";
            seen[i] = true;
            break;
        }
    }
    for (ll i = 0; i < 4; i++) {
        if (!seen[i]) {
            cout << i + 1;
            break;
        }
    }
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}