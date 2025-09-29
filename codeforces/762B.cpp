#include <bits/stdc++.h>
using ll = long long;
using ld = long double;
using pll = std::pair<long long, long long>;
using namespace std;
#define M_PI 3.14159265358979323846
const long long INF = 2e18;
const long long MOD = 1000000007;

void solve() {
    ll a, b, c, m, val;
    cin >> a >> b >> c >> m;
    vector<pll> mouse(m);
    string type;
    for (ll i = 0; i < m; i++) {
        cin >> val >> type;
        if (type == "USB") mouse[i] = {val, 0};
        else mouse[i] = {val, 1};
    }
    sort(mouse.begin(), mouse.end());
    ll comp = 0, cost = 0;
    for (ll i = 0; i < m; i++) {
        if (mouse[i].second == 0) {
            if (a == 0 && c == 0) continue;
            comp++;
            cost += mouse[i].first;
            if (a == 0) c--;
            else a--;
        }
        else if (mouse[i].second == 1) {
            if (b == 0 && c == 0) continue;
            comp++;
            cost += mouse[i].first;
            if (b == 0) c--;
            else b--;
        }
    }
    cout << comp << " " << cost;
} 

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout << setprecision(20);

    solve();
    return 0;
}