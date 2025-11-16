#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

void solve() {
    map<string, ll> colors{
        {"green", 0},
        {"yellow", 1},
        {"orange", 2},
        {"red", 3},
        {"purple", 4},
        {"violet", 5},
        {"blue", 6},
        {"blue-green", 7}
    };
    string a, b;
    cin >> a >> b;
    cout << min((8 + colors[b] - colors[a]) % 8, (8 + colors[a] - colors[b]) % 8) << "\n";
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    int t; cin >> t; while (t--) solve();
    return 0;
}