#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

void solve() {
    ll n, m;
    cin >> n >> m;
    vector<ll> d;
    while (n != 0) {
        d.push_back(n % m);
        n /= m;
    }
    sort(d.begin(), d.end());
    for (ll i = 0; i < d.size() - 1; i++) {
        if (d[i] == d[i + 1]) {
            cout << "NO\n";
            return;
        }
    }
    cout << "YES\n";
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}