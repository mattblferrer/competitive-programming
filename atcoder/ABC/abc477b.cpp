#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1'000'000'007;

void solve() {
    ll n, d;
    cin >> n >> d;
    vector<ll> x(n);
    for (ll i = 0; i < n; i++) cin >> x[i];

    vector<ll> p;
    for (ll i = 0; i < n; i++) {
        bool apart = true;
        for (ll j = 0; j < n; j++) {
            if (i == j) continue;
            if (abs(x[i] - x[j]) < d) {
                apart = false;
                break;
            }
        }
        if (apart) p.push_back(i + 1);
    }
    cout << p.size() << "\n";
    for (ll i = 0; i < p.size(); i++) cout << p[i] << " ";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}