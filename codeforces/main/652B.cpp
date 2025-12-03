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
    vector<ll> a(n);
    for (ll i = 0; i < n; i++) cin >> a[i];
    sort(a.begin(), a.end());
    vector<ll> b(n);
    for (ll i = 0; i < n; i++) {
        if (2*i < n) b[2*i] = a[i];
        else b[2*(i - (n + 1)/2) + 1] = a[i];
    }
    for (ll i = 0; i < n; i++) cout << b[i] << " ";
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}