#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

void solve() {
    ll a, b, x;
    cin >> a >> b >> x;
    ll left = 0, right = 1'000'000'001;
    while (right - left > 1) {
        ll mid = (left + right) / 2;
        ll cost = a * mid + b * to_string(mid).size();
        if (cost <= x) left = mid;
        else right = mid;
    }
    cout << left << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}