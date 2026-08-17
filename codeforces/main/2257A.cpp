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
    set<char> start;
    for (ll i = 0; i < n; i++) {
        string wi;
        cin >> wi;
        start.insert(wi[0]);
    }

    bool possible = true;
    for (ll i = 0; i < m; i++) {
        string ai;
        cin >> ai;
        for (ll j = 0; j < ai.size(); j++) {
            if (start.count(tolower(ai[j])) == 0) {
                possible = false;
                break;
            }
        }
    }
    if (possible) cout << "YES\n";
    else cout << "NO\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    int t; cin >> t; while (t--) solve();
    return 0;
}