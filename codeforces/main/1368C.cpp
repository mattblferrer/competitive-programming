#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

struct point {
    int x, y;
};

void solve() {
    int n;
    cin >> n;
    vector<point> p ;
    p.push_back({0, 0});
    p.push_back({0, 1});
    for (int i = 1; i <= n; i++) {
        for (int j = i - 1; j <= i + 1; j++) {
            p.push_back({i, j});
        }
    }
    p.push_back({n + 1, n});
    p.push_back({n + 1, n + 1});
    cout << p.size() << "\n";
    for (int i = 0; i < p.size(); i++) cout << p[i].x << " " << p[i].y << "\n";
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}