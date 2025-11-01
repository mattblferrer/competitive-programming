#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

void solve() {
    ll n, k;
    cin >> n >> k;
    string road;
    cin >> road;
    ll curr = 0;
    for (ll i = 0; i < n; i++) {
        if (road[i] == '.') {
            curr = 0;
        }
        else curr++;
        if (curr == k) {
            cout << "NO\n";
            return;
        }
    }
    cout << "YES\n";
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}