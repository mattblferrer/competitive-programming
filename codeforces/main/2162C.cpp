#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

void solve() {
    ll a, b;
    cin >> a >> b;
    vector<int> xs;
    for (int i = 0; (1 << i) <= max(a, b); i++) {
        int bita = a & (1 << i);
        int bitb = b & (1 << i);
        int curr = bita ^ bitb;
        if (curr == 0) continue;
        if (curr <= a) xs.push_back(curr);
        else {
            cout << "-1\n";
            return;
        }
    }
    cout << xs.size() << "\n";
    for (int x: xs) cout << x << " ";
    cout << "\n";
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    int t; cin >> t; while (t--) solve();
    return 0;
}