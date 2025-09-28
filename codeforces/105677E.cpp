#include <bits/stdc++.h>
using ll = long long;
using ld = long double;
using pll = std::pair<long long, long long>;
using namespace std;
#define M_PI 3.14159265358979323846
const long long INF = 2e18;
const long long MOD = 1000000007;
 
void solve() {
    ll n, x, y;
    cin >> n;
    map<ll, vector<ll>> px;
    for (ll i = 0; i < n; i++) {
        cin >> x >> y;
        px[x].push_back(y);
    }
    deque<pll> ans;
    set<pll> used;
    vector<ll> used_x;
    auto pb_unique = [&](ll x, ll y) {
        if (used.count({x, y}) == 0) {
            ans.push_back({x, y});
            used.insert({x, y});
        }
    };
    
    for (const auto& pair: px) used_x.push_back(pair.first);
    for (ll i = 0; i < used_x.size(); i++) {
        x = used_x[i];
        auto ys = px[used_x[i]];
        sort(ys.begin(), ys.end());
        if (i == 0) pb_unique(x, 1);
        else pb_unique(x, 2);
        for (ll y: ys) {
            if (y >= 2) pb_unique(x, y);
        }
        if (i == used_x.size() - 1) {
            if (x < 1000000000) pb_unique(x + 1, 2);
            else pb_unique(x - 1, 2);
        }
        else pb_unique(x + 1, 2);
    }
    sort(ans.begin(), ans.end(), [](pll a, pll b) {
        if (a.first == b.first) {
            if (a.first == 1000000000) return a.second > b.second;
            else return a.second < b.second;
        }
        return a.first < b.first;
    });
    int ones = 0;
    for (ll i = used_x.size() - 1; i >= 0; i--) {
        x = used_x[i];
        auto ys = px[used_x[i]];
        sort(ys.begin(), ys.end());
        if (ys[0] == 1) {
            pb_unique(x, 1);
            ones++;
        }
    }
    cout << ans.size() << "\n";
    for (pll p: ans) {
        cout << p.first << " " << p.second << "\n";
    }
} 
 
int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout << setprecision(20);
 
    solve();
    return 0;
}