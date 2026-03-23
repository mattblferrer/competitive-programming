#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

void solve() {
    ll n, m;
    cin >> n >> m;
    ll pts = 0, side = 0, time = 0;
    for (ll i = 0; i < n; i++) {
        ll ai, bi;
        cin >> ai >> bi;
        if ((abs(side - bi)) % 2 == (ai - time) % 2) pts += ai - time;
        else pts += ai - time - 1;
        time = ai;
        side = bi;
    }
    pts += m - time;
    cout << pts << "\n";
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    int t; cin >> t; while (t--) solve();
    return 0;
}