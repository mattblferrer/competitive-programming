#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

bool is_pandigital(ll n) {
    string to_str = to_string(n);
    sort(to_str.begin(), to_str.end());
    for (int i = 0; i < to_str.size(); i++) {
        if (to_str[i] - '0' == 0) return false;
        if (to_str[i] - '0' > to_str.size()) return false;
    }
    for (int i = 0; i < to_str.size() - 1; i++) {
        if (to_str[i] == to_str[i + 1]) return false;
    }
    return true;
}

void solve() {
    ll ans = 0;
    for (ll i = 0; i < 10000; i++) {
        string curr_str = "";
        ll mult = 1;
        while (curr_str.size() < 9) {
            curr_str += to_string(i * mult);
            mult++;
        }
        if (curr_str.size() != 9) continue;
        ll curr = stoll(curr_str);
        if (is_pandigital(curr)) ans = max(ans, curr);
    }
    cout << ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}