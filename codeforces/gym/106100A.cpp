#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

void solve() {
    int n, m, pi;
    cin >> n >> m;
    vector<int> seen(n + 1);
    for (int i = 0; i < m; i++) {
        cin >> pi;
        seen[pi]++;
    }
    for (int i = 1; i <= n; i++) {
        if (!seen[i]) cout << i << " ";
    }
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}