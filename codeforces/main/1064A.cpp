#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

void solve() {
    vector<int> sides(3);
    for (int i = 0; i < 3; i++) cin >> sides[i];
    sort(sides.begin(), sides.end());
    int ans = max(0, sides[2] - sides[1] - sides[0] + 1);
    cout << ans;
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);
    
    solve();
    return 0;
}