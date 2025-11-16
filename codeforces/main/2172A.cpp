#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

void solve() {
    vector<ll> a(3);
    for (ll i = 0; i < 3; i++) cin >> a[i];
    sort(a.begin(), a.end());
    if (a[2] - a[0] >= 10) cout << "check again";
    else cout << "final " << a[1];
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);
    solve();
    return 0;
}