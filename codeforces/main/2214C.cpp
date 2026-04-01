#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

void solve() {
    vector<ll> abc(3);
    for (ll i = 0; i < 3; i++) cin >> abc[i];
    sort(abc.begin(), abc.end());
    ll x = 0;
    for (ll i = 0; i < 3; i++) x ^= abc[i];
    cout << x - abc[1] << "\n";
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    int t; cin >> t; while (t--) solve();
    return 0;
}