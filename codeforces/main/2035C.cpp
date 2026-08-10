#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

void solve() {
    int n;
    cin >> n;
    vector<ll> p(n + 1);
    for (int i = 1; i <= n; i++) p[i] = i;
    if (n % 2 == 1) {
        swap(p[1], p[n - 3]);
        swap(p[3], p[n - 2]);
    }
    else if (__builtin_popcount(n) == 1) {  // power of two
        swap(p[1], p[n - 4]);
        swap(p[3], p[n - 3]);
    }
    else {
        swap(p[n - 2], p[n]);
        swap(p[(1 << (__bit_width(n)) - 1) - 1], p[n]);
    }

    int k = 0;
    for (int i = 1; i <= n; i++) {
        if (i % 2 == 1) k &= p[i];
        else k |= p[i];
    }
    cout << k << "\n";
    for (int i = 1; i <= n; i++) cout << p[i] << " ";
    cout << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    int t; cin >> t; while (t--) solve();
    return 0;
}