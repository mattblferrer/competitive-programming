#include <bits/stdc++.h>
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
    ll ans = (n % 3)*3, ctr = 1, big = 9, small = 1;
    n /= 3;
    while (n > 0) {
        ans += (n % 3)*(big + ctr*small);
        ctr++;
        big *= 3;
        small *= 3; 
        n /= 3;
    }
    cout << ans << "\n";
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    int t; cin >> t; while (t--) solve();
    return 0;
}