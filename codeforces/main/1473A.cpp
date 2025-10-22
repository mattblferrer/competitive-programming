#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

void solve() {
    int n, d;
    cin >> n >> d;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    bool is_less = true;
    for (int i = 0; i < n; i++) {
        if (a[i] > d) {
            is_less = false;
            break;
        }
    }
    if (is_less) {
        cout << "YES\n";
        return;
    }
    int min_pair = MOD;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) continue;
            if (a[i] + a[j] < min_pair) min_pair = a[i] + a[j];
        }
    }
    if (min_pair <= d) cout << "YES\n";
    else cout << "NO\n";
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    int t; cin >> t; while (t--) solve();
    return 0;
}