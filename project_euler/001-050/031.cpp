#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

void solve() {
    vector<ll> coins = {1, 2, 5, 10, 20, 50, 100, 200};
    vector<vector<ll>> ways(201, vector<ll>(coins.size() + 1));
    ways[0][0] = 1;
    for (ll i = 0; i <= 200; i++) {
        for (ll j = 0; j < coins.size(); j++) {
            if (i == 0) ways[i][j] = 1;
            else if (j == 0) ways[i][j] = ways[i - coins[j]][j];
            else if (coins[j] > i) ways[i][j] = ways[i][j - 1];
            else ways[i][j] = ways[i][j - 1] + ways[i - coins[j]][j];
        }
    }
    cout << ways[200][coins.size() - 1];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}