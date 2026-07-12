#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

void solve() {
    ll n, k, m;
    cin >> n >> k >> m;
    map<ll, vector<ll>> div;
    for (ll i = 0; i < n; i++) {
        ll ai;
        cin >> ai;
        div[ai % m].push_back(ai);
    }
    for (const auto &pair : div) {
        if (pair.second.size() >= k) {
            cout << "Yes\n";
            for (ll i = 0; i < k; i++) cout << pair.second[i] << " ";
            return;
        }
    }
    cout << "No\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}