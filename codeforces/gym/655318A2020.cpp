#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

void solve() {
    ll n;
    cin >> n;
    vector<ll> b(n);
    for (ll i = 0; i < n; i++) cin >> b[i];
    sort(b.begin(), b.end());
    cout << b[0] << " ";
    for (ll i = 0; i < n - 1; i++) cout << b[i + 1] - b[i] << " ";
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}