#include <iomanip>
#include <iostream>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

void solve() {
    ll n; 
    cin >> n;
    vector<ll> ways(4), nways(4);
    ways[0] = 1;
    for (ll i = 0; i < n; i++) {
        for (ll j = 0; j < 4; j++) {
            nways[j] = 0;
        }
        for (ll j = 0; j < 4; j++) {
            for (ll k = 0; k < 4; k++) {
                if (j == k) continue;
                nways[k] = (nways[k] + ways[j]) % MOD; 
            }
        }
        swap(ways, nways);
    }
    cout << ways[0] << "\n";
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}