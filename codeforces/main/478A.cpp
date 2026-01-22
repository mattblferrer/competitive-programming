#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

void solve() {
    vector<ll> c(5);
    ll sum = 0;
    for (ll i = 0; i < 5; i++) {
        cin >> c[i];
        sum += c[i];
    }
    if (sum == 0) cout << -1;
    else if (sum % 5 != 0) cout << -1;
    else cout << sum / 5;
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}