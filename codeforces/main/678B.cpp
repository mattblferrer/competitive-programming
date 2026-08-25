#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1'000'000'007;

bool is_leap_year(ll year) {
    if (year % 400 == 0) return true;
    if (year % 100 == 0) return false;
    if (year % 4 == 0) return true;
    return false;
}

void solve() {
    ll y;
    cin >> y;
    bool start_ly = is_leap_year(y);
    ll ans = y + 1, curr = is_leap_year(y + 1) ? (366 % 7) : (365 % 7);
    while ((curr % 7 != 0) || (is_leap_year(ans) != start_ly)) {
        ans++;
        curr += is_leap_year(ans) ? (366 % 7) : (365 % 7);
    }
    cout << ans << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}