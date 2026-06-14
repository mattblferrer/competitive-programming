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
    vector<pll> years;
    for (ll i = 0; i < n; i++) {
        ll b, d;
        cin >> b >> d;
        years.push_back({b, 1});
        years.push_back({d, -1});
    }
    sort(years.begin(), years.end());
    ll curr_k = 0, k = 0, y = -1;
    for (ll i = 0; i < 2 * n; i++) {
        ll curr_y = years[i].first, event = years[i].second;
        curr_k += event;
        if (curr_k > k) {
            k = curr_k;
            y = curr_y;
        }
    }
    cout << y << " " << k << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}