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
    ll curr = 1;
    vector<ll> y;
    for (ll i = 0; i < n; i++) {
        if (a[i] == curr) {
            y.push_back(2001 + i);
            curr++;
        }
    }
    cout << y.size() << "\n";
    for (ll i = 0; i < y.size(); i++) cout << y[i] << " ";
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}