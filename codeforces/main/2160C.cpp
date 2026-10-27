#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1'000'000'007;

bool solve(ll n) {
    while ((n > 0) && (n % 2 == 0)) n /= 2;

    vector<bool> bits;
    while (n > 0) {
        bits.push_back(n & 1);
        n /= 2;
    }
    int cnt = 0;
    for (int i = 0; i < bits.size(); i++) {
        if (bits[i] == 1) cnt++;
    }
    if (cnt % 2 == 1) return false;
    for (int i = 0; i < bits.size(); i++) {
        if (bits[i] != bits[bits.size() - i - 1]) return false;
    }
    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    int t; cin >> t; while (t--) {
        ll n;
        cin >> n;
        if (solve(n)) cout << "YES\n";
        else cout << "NO\n";
    }
    return 0;
}