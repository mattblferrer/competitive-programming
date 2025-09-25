#include <bits/stdc++.h>
using ll = long long;
using ld = long double;
using pll = std::pair<long long, long long>;
using namespace std;
#define M_PI 3.14159265358979323846
const long long INF = 2e18;
const long long MOD = 1000000007;

void solve() {
    ll n, q;
    cin >> n >> q;
    vector<ll> x(n + 1), pref(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> x[i];
        pref[i] = pref[i - 1] + x[i];
    }
    ll a, b;
    for (int i = 1; i <= q; i++) {
        cin >> a >> b;
        cout << pref[b] - pref[a - 1] << "\n";
    }
} 

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout << setprecision(20);

    solve();
    return 0;
}