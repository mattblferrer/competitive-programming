#include <bits/stdc++.h>
using ll = long long;
using ld = long double;
using pll = std::pair<long long, long long>;
using namespace std;
#define M_PI 3.14159265358979323846
const long long INF = 2e18;
const long long MOD = 1000000007;

void solve() {
    ll n, m;
    cin >> n >> m;
    vector<vector<ll>> ids(m);
    ll need[m][10];
    memset(need, 0, sizeof(need));
    ll raw[10];
    memset(raw, 0, sizeof(raw));
    ll raw_ctr = 0;
    for (ll i = 0; i < m; i++) {
        ll c_i, p_i;
        cin >> c_i;
        if (c_i == 0) {
            cin >> p_i;
            need[i][raw_ctr] = 1;
            raw[raw_ctr] = p_i;
            raw_ctr++;
        }
        else {
            for (ll j = 0; j < c_i; j++) {
                ll id;
                cin >> id;
                ids[i].push_back(id - 1);
            }
        }
    }
    for (ll i = m - 1; i >= 0; i--) {
        for (ll j = 0; j < ids[i].size(); j++) {
            ll id = ids[i][j];
            for (ll k = 0; k < 10; k++) {
                need[i][k] = min(need[i][k] + need[id][k], MOD);
            }
        }
    }
    ll ans = 0;
    for (ll i = 0; i < (1 << n); i++) {
        ll cur_raw[10];
        memset(cur_raw, 0, sizeof(cur_raw));
        for (ll j = 0; j < n; j++) {
            if (!(i & (1 << j))) continue;
            for (ll k = 0; k < 10; k++) {
                cur_raw[k] += need[j][k];
            }
        }
        bool valid = true;
        for (ll j = 0; j < 10; j++) {
            if (cur_raw[j] > raw[j]) valid = false;
        }
        if (valid) ans = max(ans, (ll)__builtin_popcount(i));
    }
    cout << ans << "\n";
} 

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout << setprecision(20);

    solve();
    return 0;
}